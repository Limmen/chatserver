-module(client).
-compile(export_all).
-define(TCP_OPTIONS,[list, {packet, 0}, {active, false}]).

connect() ->
    Server = "localhost", % to make it runnable on one machine
    {ok, ServerSocket} = gen_tcp:connect(Server, 2000, ?TCP_OPTIONS),
    register(rc, spawn_link(fun()-> recv(ServerSocket) end)),
    chat(ServerSocket).

chat(ServerSocket)->
    Line = io:get_line(">"),
    gen_tcp:send(ServerSocket, Line),
    chat(ServerSocket).

recv(ServerSocket) ->
    case gen_tcp:recv(ServerSocket, 0) of
        {ok, Raw_msg} ->
            Msg = hd(string:tokens(Raw_msg, "\r\n")),
            io:format(Msg),
            recv(ServerSocket);
        {error, closed} ->
            ok
    end.
