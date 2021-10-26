FROM gcc:11 as build
WORKDIR /app
COPY rat.cpp .
RUN g++ -std=gnu++11 -pedantic rat.cpp -o rat
CMD ["/app/rat"]
