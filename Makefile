all: build

build:
	rebar3 compile
	erlc clients/erlang_client/client.erl

run_server: 
	erl -pa _build/default/lib/chat/ebin -eval "application:start(chat)" -noshell start_sasl


run_client: 
	erl -pa clients/erlang_client -s client connect -noshell

