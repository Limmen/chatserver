-module(listener).

%% API exports
-export([spawn_socket/1]).


%%====================================================================
%% API
%%====================================================================

spawn_socket(Port)->
    io:format("Hello my pid is: ~p ~n I am supposed to create a listening socket on port: ~p. But instead I'm going to exit now. ~n", [self(), Port]),
    spawn_link(fun()-> wait() end),
    {ok, self()}. %%% Varför klagar supervisor om vi inte returnerar detta?.
    

%%====================================================================
%% Internal functions
%%====================================================================
wait()->
    receive
        _ ->
            io:format("received")
                end.
