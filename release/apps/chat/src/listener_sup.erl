-module(listener_sup).

-behaviour(supervisor).

-define(TCP_OPTIONS,[binary, {packet, 0}, {active, false}, {reuseaddr, true}]).


%API
-export([start_link/2]).

%% Application callbacks
-export([init/1]).


%%====================================================================
%% API
%%====================================================================

start_link(Port, Listeners) ->
    supervisor:start_link({local, listener_sup}, listener_sup, [Port, Listeners]).

%%====================================================================
%% Supervisor callbacks
%%====================================================================

init([Port,Listeners]) ->
    
    {ok, ServerSocket} = gen_tcp:listen(Port, ?TCP_OPTIONS),

    SupFlags = #{strategy => one_for_one,   
                intensity => 1, 
                period => 3},       
    Create_workers = fun() -> {make_ref(),
                        {listener, spawn_socket, [ServerSocket]},
                        permanent, brutal_kill, worker, [listener]}
                     end,

    %% Creates specs for <n> number of accepting processes
    _Workers = [Create_workers() || _ <- lists:seq(0, Listeners)],
    {ok, {SupFlags, _Workers}}.
    

    

%%====================================================================
%% Internal functions
%%====================================================================
