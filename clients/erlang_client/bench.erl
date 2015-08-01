-module(bench).
-compile(export_all).

start(N) ->
    Start = now(),
    run(N),
    return(N),
    Finish = now(),
    timer:now_diff(Finish, Start).

run(0)->
    ok;
run(N)->
    spawn_monitor(fun()-> client:connect() end),
    run(N-1).

return(0)->
    erlang:display("done! all threads returned"),
    ok;

return(N)->
   receive
       {'DOWN', _, process, _, _} ->  
           return(N-1)
		     end.	    
