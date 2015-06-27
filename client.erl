-module(client).
-compile(export_all).
-define(TCP_OPTIONS,[list, {packet, 0}, {active, false}]).

connect(Port) ->
    Server = "localhost", % to make it runnable on one machine
    {ok, ServerSocket} = gen_tcp:connect(Server, Port, ?TCP_OPTIONS),
    chat(ServerSocket).

chat(ServerSocket)->
    register(rc, spawn_link(fun()-> recv(ServerSocket) end)),
    setup(ServerSocket).

setup(ServerSocket)->
    Name = io:get_line("Enter username:"),
    case Name of
        [$E,$X,$I,$T,10] -> 
            leave(ServerSocket);
        _ ->
            gen_tcp:send(ServerSocket,Name),
            send(ServerSocket, Name)
                end.

send(ServerSocket, Name) ->
    Line = io:get_line("Enter message: "),
    case Line of
        [$E,$X,$I,$T,10] -> leave(ServerSocket);
        _ ->
            gen_tcp:send(ServerSocket, Line),
            send(ServerSocket, Name)
                end.


recv(ServerSocket) ->
    case gen_tcp:recv(ServerSocket, 0) of
        {ok, Data} ->
            io:format("~s ~n", [Data]),
            recv(ServerSocket);
        {error, closed} ->
                    io:format("Connection was lost"),           
                    ok
                end.

leave(ServerSocket) ->
    io:format("~n leave"),
    ok = gen_tcp:close(ServerSocket),
    exit(ok).
        
