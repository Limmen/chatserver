-module(chat_server).

-behaviour(gen_server).

%% Gen_server callbacks
-export([init/1]).

%API
-export([start_link/1, handle_call/3, handle_cast/2, handle_info/2, terminate/2]).



%%====================================================================
%% API
%%====================================================================

start_link(Args) ->
    io:format("Chatserver is starting up ~n"),
    gen_server:start_link({local, chat_server}, chat_server, Args, []).

%%====================================================================
%% Gen_server callbacks
%%====================================================================

init(_) ->
    io:format("Chatservers init func was called by gen_server ~n"),
    {ok, []}.
    
handle_call(_, _,_) ->
    io:format("handle, call inside chat_server ~n"),
    {reply, [], []}.

handle_cast(_,_) ->
    io:format("handle_cast inside chat_server ~n"),
    {noreply, []}.

handle_info(_, _) ->
    io:format("Unexpected message: inside handle_server ~n"),
    {noreply, []}.

terminate(_,_) ->
    io:format("chat_server terminating ~n"),
    ok.
%%====================================================================
%% Internal functions
%%====================================================================
