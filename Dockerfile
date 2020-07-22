FROM amytabb/docker_ubuntu16_essentials

RUN apt-get update \
    && apt-get install -y software-properties-common \
    && add-apt-repository ppa:ubuntu-toolchain-r/test -y \
    && apt-get update \
    && apt-get install -y libstdc++6 \ 
    && apt-get install -y build-essential

COPY . / 
RUN make
CMD ["./main"]
