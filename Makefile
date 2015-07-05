all: build

build:
	rebar3 compile
	erlc client/client.erl

run_server: 
	erl -pa _build/default/lib/chat/ebin -eval "application:start(chat)" -noshell


run_client: 
	erl -pa client -s client connect -noshell

