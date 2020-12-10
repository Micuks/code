while true; do
./compare $RANDOM > data.in
./t2_std < data.in > std.out
./t2 < data.in > data.out
    if diff data.out std.out ; then
        printf "AC\n"
    else
        printf "WA\n"
        exit 0;
    fi
done