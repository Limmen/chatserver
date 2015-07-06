-module(client_handler).


-export([clientSetup/1]).


%%====================================================================
%% API
%%====================================================================
clientSetup(ClientSocket) ->
    io:format("setting upp client!! ~n"),
    gen_tcp:send(ClientSocket, <<"Enter username> \r\n">>),
    io:format("ClientHandler waiting for username"),
    case gen_tcp:recv(ClientSocket, 0) of
        {ok, Raw_msg} ->
            %%hd returns head of string-split on tokens (\r\n (CRLF)).
            io:format("ClientHandler received username ~n"),
            UserName = binary:bin_to_list(Raw_msg),
           %% UserName = hd(string:tokens(Raw_msg, "\r\n")), 
            chat_server:reg_client(ClientSocket, UserName),
            chat(ClientSocket, UserName);
        {error, closed} ->
            ok
    end.

%%====================================================================
%% Internal functions
%%====================================================================
chat(ClientSocket, UserName) ->
    case gen_tcp:recv(ClientSocket, 0) of
        {ok, Raw_msg} ->
      %      Msg = hd(string:tokens(Raw_msg, "\r\n")),
            Msg = binary:bin_to_list(Raw_msg),
            case Msg of
                "exit" -> chat_server:broadcast_client_left(ClientSocket,UserName);
                "Exit" -> chat_server:broadcast_client_left(ClientSocket,UserName);
                "EXIT" -> chat_server:broadcast_client_left(ClientSocket,UserName);
                "--active" -> chat_server:broadcast_active_clients();
                _          -> chat_server:broadcast(Msg)
            end,
            chat(ClientSocket, UserName);
        {error, closed} ->
            ok
    end.
