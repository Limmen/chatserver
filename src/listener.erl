-module(listener).

%% API exports
-export([spawn_socket/1]).


%%====================================================================
%% API
%%====================================================================

spawn_socket(ServerSocket)->
    io:format("new listener up and waiting for clients to connect ~n"),
    spawn_link(fun()-> accept(ServerSocket) end),
    {ok, self()}. %%% Varför klagar supervisor om vi inte returnerar detta?.
    

%%====================================================================
%% Internal functions
%%====================================================================

accept(ServerSocket) ->
    {ok, ClientSocket} = gen_tcp:accept(ServerSocket),
    io:format("new client connected /listener ~n"),
    spawn(fun() -> client_handler:clientSetup(ClientSocket) end),
    accept(ServerSocket).
