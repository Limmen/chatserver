-module(listener).

%% API exports
-export([spawn_socket/1]).


%%====================================================================
%% API
%%====================================================================

spawn_socket(ServerSocket)->
    spawn_link(fun()-> accept(ServerSocket) end),
    {ok, self()}. %%% Varför klagar supervisor om vi inte returnerar detta?.
    

%%====================================================================
%% Internal functions
%%====================================================================

accept(ServerSocket) ->
    {ok, ClientSocket} = gen_tcp:accept(ServerSocket),
    io:format("Client connected! ~n"),
    spawn(fun() -> client_handler:clientSetup(ClientSocket) end),
    accept(ServerSocket).
