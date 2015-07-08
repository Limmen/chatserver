-module(client_handler).


-export([clientSetup/1]).


%%====================================================================
%% API
%%====================================================================
clientSetup(ClientSocket) ->
    gen_tcp:send(ClientSocket, <<"<Server> Enter username \r\n">>),
    case gen_tcp:recv(ClientSocket, 0) of
        {ok, Raw_msg} ->
            UserName = binary:bin_to_list(Raw_msg),
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
            chat_server:broadcast_client_left(ClientSocket,UserName),
            exit("Client left")
    end.
