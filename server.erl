-module(server).
-compile(export_all).
-define(TCP_OPTIONS,[list, {packet, 0}, {active, false}, {reuseaddr, true}]).
start(Port) ->
    register(server, spawn(fun() -> listen(Port) end )).

stop() ->
    exit(whereis(server), "time to die").

listen(Port) ->
    case gen_tcp:listen(Port, ?TCP_OPTIONS) of
        {ok, ServerSocket} ->
            io:format("Chatserver up and running on port ~B ~n", [Port]),
            spawn_link(fun() -> accept(ServerSocket) end),
            wait([]);
        {error, _} -> 
            error
                end.

wait(Clients)->
    receive
        {client, Pid} ->
            wait([Pid|Clients]);
        {message, M} ->
            spawn(fun() -> broadcast(Clients,M) end),
            wait(Clients)
                end.

broadcast([], _) ->
    done;
broadcast([H|T], {N,M}) ->
    H ! {server, N++[58|M]},
    broadcast(T, {N,M}).

accept(ServerSocket) ->
    case gen_tcp:accept(ServerSocket) of
        {ok, ClientSocket} ->
            server ! {message, {"Server","new client entered the chatroom"}},
            spawn(fun() -> clientSetup(ClientSocket) end),
            HandlerPid = spawn(fun() -> updateClient(ClientSocket) end),
            server ! {client,HandlerPid},
            accept(ServerSocket);
        {error, _} -> error
                              end.

clientSetup(ClientSocket)->
    case gen_tcp:recv(ClientSocket, 0) of
        {ok, Name} ->
            io:format("Server received username: ~s ~n", [Name]),
            clientResponse(ClientSocket, Name);
        {error, closed} ->
            ok
    end.

clientResponse(ClientSocket, Name) ->
    case gen_tcp:recv(ClientSocket, 0) of
        {ok, Data} ->
            server ! {message,{Name,Data}},
           clientResponse(ClientSocket, Name);
        {error, closed} ->
            ok
    end.

updateClient(ClientSocket) ->
    receive
        {server, M} ->
            gen_tcp:send(ClientSocket, M),
            updateClient(ClientSocket)
                end.
            
            
            
