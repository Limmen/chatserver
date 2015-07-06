-module(chat_server).

-behaviour(gen_server).

%% Gen_server callbacks
-export([init/1, handle_call/3, handle_cast/2, handle_info/2, terminate/2, code_change/3]).

%API
-export([start_link/0, stop/0]).

-export([
         reg_client/2,
         broadcast/1,
         broadcast_active_clients/0,
         broadcast_client_left/2]).

-record(state, {clients}).
-record(client, {pid, socket, name}).

%%====================================================================
%% API
%%====================================================================

start_link() ->
    process_flag(trap_exit, true), %% TODOOOOOOOOOOO
    gen_server:start_link({local, chat_server}, chat_server, [], []).

stop() ->
    gen_server:call(?MODULE, stop).

%%====================================================================
%% Gen_server callbacks
%%====================================================================

init([]) ->
    %%Empty list cause 0 clients.
    {ok, #state{clients=[]}}.
    
handle_call({reg_client,ClientSocket,UserName},{Pid, _},State) ->
    io:format("Client ~p connected from ~p~n", [UserName, Pid]),
    link(Pid),
    Client = #client{pid=Pid, name=UserName, socket=ClientSocket},
    NewState = State#state{clients=[Client|State#state.clients]},
    broadcast(NewState#state.clients,"<Server>" ++ UserName ++ " has joined\n"),
    {reply, ok, NewState};

handle_call({remove_client,_,UserName},{Pid, _},State) ->
    io:format(UserName ++ "leaving"),
    Clients = [Client || Client <- State#state.clients, Client#client.pid /= Pid],
    NewState = State#state{clients=Clients},
    broadcast(NewState#state.clients,"<Server>" ++ UserName ++ " has left\n"),
    {reply, ok, NewState}.

%% Remove client from the current list
handle_cast({remove_client, Pid}, State) ->
    Clients = [Client || Client <- State#state.clients, Client#client.pid /= Pid],
    NewState = State#state{clients=Clients},
    {noreply, NewState};

%% Broadcast generic message
handle_cast({broadcast, Msg, Pid}, State) ->
    Client = find_client(State#state.clients, Pid),
    Str = "<" ++ Client#client.name ++ ">" ++ Msg ++ "\n",
    broadcast(State#state.clients, Str),
    io:format(Str),
    {noreply, State};

%% Broadcast the active clients to the client requesting it
handle_cast({broadcast_active_clients, Pid}, State) ->
    Client = find_client(State#state.clients, Pid),
    broadcast([Client], get_active_clients(State#state.clients)),
    {noreply, State};

handle_cast(_Other, State) ->
    io:format("[Debug] Server got strange message: ~p~n", [_Other]),
    {noreply, State}.


% Handle clients dying
handle_info({'EXIT', From, _}, State) ->
    io:format("server got EXIT signal from: " ++ From),
    Msg = find_client(State#state.clients, From) ++ " has left",
    broadcast(State#state.clients, Msg),
    NewState = [Cli || Cli <- State#state.clients, Cli /= From],
    {noreply, NewState};

handle_info(_Info, State) ->
    {noreply, State}.

terminate(_Reason, _State) ->
    ok.

code_change(_OldVsn, State, _Extra) ->
    {ok, State}.
%%====================================================================
%% Client API
%%====================================================================


reg_client(ClientSocket, UserName) ->
    io:format("sending reg-client call to gen_server ~n"),
    gen_server:call(?MODULE, {reg_client, ClientSocket, UserName}).

broadcast(Msg) ->
    gen_server:cast(?MODULE, {broadcast, Msg, self()}).

broadcast_active_clients() ->
    gen_server:cast(?MODULE, {broadcast_active_clients, self()}).

broadcast_client_left(ClientSocket, UserName) ->
    gen_server:call(?MODULE, {remove_client, ClientSocket, UserName}).


%%%===================================================================
%%% Internal functions
%%%===================================================================

broadcast(Clients, Msg) ->
    [gen_tcp:send(Cli#client.socket, Msg) || Cli <- Clients].


find_client(Clients, Pid) ->
    hd([Cli || Cli <- Clients, Cli#client.pid == Pid]).


get_active_clients(Clients) ->
  CliNames = [Cli#client.name ++ "\n" || Cli <- Clients],
  Msgs = ["<Server> Clients currently active:",
          "---",
          CliNames,
          "---\n"],
  string:join(Msgs, "\n").
