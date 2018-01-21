FROM jjanzic/docker-python3-opencv

WORKDIR /

ENV STASM_VERSION="stasm4.1.0"
RUN wget http://www.milbo.org/stasm-files/6/${STASM_VERSION}.tar.gz \
  && tar -xvzf ${STASM_VERSION}.tar.gz \
  && rm ${STASM_VERSION}.tar.gz \
  && cd ${STASM_VERSION} \
  && git clone https://github.com/alyssaq/stasm_build.git \
  && ./stasm_build/build.sh
