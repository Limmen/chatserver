FROM ubuntu:trusty

RUN apt-get update && apt-get -y upgrade && apt-get -y install wget && apt-get -y install git git-core

RUN cd /tmp; wget https://packages.erlang-solutions.com/erlang-solutions_1.0_all.deb && \
    dpkg -i erlang-solutions_1.0_all.deb

RUN apt-get update && apt-get -y install erlang erlang-base-hipe build-essential

RUN git clone https://github.com/rebar/rebar3.git

RUN cd rebar3; ./bootstrap; cp rebar3 /bin/rebar3;

RUN echo "export PATH=$PATH:/bin/rebar3" >> ~/.bashrc

RUN git clone https://github.com/Limmen/chatserver.git

EXPOSE 2000

CMD cd chatserver; make; make run_server

