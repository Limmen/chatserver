%%%-------------------------------------------------------------------
%% @doc chat top level supervisor.
%% @end
%%%-------------------------------------------------------------------

-module('chat_sup').

-behaviour(supervisor).

%% API
-export([start_link/1]).

%% Supervisor callbacks
-export([init/1]).

-define(SERVER, ?MODULE).

%%====================================================================
%% API functions
%%====================================================================

start_link(Args) ->
    supervisor:start_link({local, ?SERVER}, ?MODULE, Args).

%%====================================================================
%% Supervisor callbacks
%%====================================================================

%% Child :: {Id,StartFunc,Restart,Shutdown,Type,Modules}
init([Port,Listeners]) ->

    SupFlags = #{strategy => one_for_one,   
                 intensity => 1, 
                 period => 3},      
 
    ServerSpecs = #{id => chat_server,
                     start => {chat_server, start_link, []},
                     restart => permanent,
                     shutdown => brutal_kill,
                     type => worker,
                     modules => [chat_server]},

    Listener_supSpecs = #{id => listener_sup,
                     start => {listener_sup, start_link, [Port, Listeners]},
                     restart => permanent,
                     shutdown => brutal_kill,
                     type => supervisor,
                     modules => [listener_sup]}, 

    {ok,{SupFlags,[ServerSpecs,Listener_supSpecs]}}.

%%====================================================================
%% Internal functions
%%====================================================================
