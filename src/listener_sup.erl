-module(listener_sup).

-behaviour(supervisor).



%API
-export([start_link/2]).

%% Application callbacks
-export([init/1]).


%%====================================================================
%% API
%%====================================================================

start_link(Port, Listeners) ->
    io:format("listener_sup is starting up. ~n"),
    supervisor:start_link({local, listener_sup}, listener_sup, [Port, Listeners]).

%%====================================================================
%% Supervisor callbacks
%%====================================================================

init([Port,Listeners]) ->
    io:format("supervisor called listener_sup init func. ~n"),
    SupFlags = #{strategy => one_for_all,   
                intensity => 0, 
                period => 1},       
    Create_workers = fun() -> {make_ref(),
                        {listener, spawn_socket, [Port]},
                        transient, brutal_kill, worker, [listener]}
                     end,

    %% Creates specs for <n> number of accepting processes
    _Workers = [Create_workers() || _ <- lists:seq(0, Listeners)],
    io:format("Initializing acceptors...\n"),
    {ok, {SupFlags, _Workers}}.
    

    

%%====================================================================
%% Internal functions
%%====================================================================