FROM gcc:11 AS builder

WORKDIR /app
COPY . .

ARG NUM_CUSTOMERS=500
ARG NUM_TRANSACTIONS=10000
ARG FED_INTEREST_RATE=435.000
ARG NDEBUG=0
ARG CONCURRENCY=0
ARG TEST_MODE=0

# Add pthread library for linking
RUN set -ex && \
    CFLAGS="-Wall -g -std=c++11 -pthread \
    -DNUM_CUSTOMERS=${NUM_CUSTOMERS} \
    -DNUM_TRANSACTIONS=${NUM_TRANSACTIONS} \
    -DFED_INTEREST_RATE=${FED_INTEREST_RATE}" && \
    if [ "${NDEBUG}" = "1" ]; then CFLAGS="${CFLAGS} -DNDEBUG"; fi && \
    if [ "${CONCURRENCY}" = "1" ]; then CFLAGS="${CFLAGS} -DCONCURRENCY"; fi && \
    if [ "${TEST_MODE}" = "1" ]; then CFLAGS="${CFLAGS} -DTEST_MODE"; fi && \
    g++ ${CFLAGS} -c Main.cpp && \
    g++ ${CFLAGS} -c Bank/Bank.cpp && \
    g++ ${CFLAGS} -c Accounts/Account.cpp && \
    g++ ${CFLAGS} -c Customers/Customer.cpp && \
    g++ ${CFLAGS} -o BankService.exe Main.o Bank.o Account.o Customer.o

FROM debian:stable-slim
WORKDIR /app
COPY --from=builder /app/BankService.exe .
COPY --from=builder /app/records ./records
CMD ["./BankService.exe"]