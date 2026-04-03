while true; do
    ./zomagenerator $RANDOM > data.in
    ./newzoma < data.in > wql.out
    ./trqzoma < data.in > trq.out
    if diff wql.out trq.out ; then
        printf "AC\n"
    else 
        printf "WA\n"
        exit 0;
    fi
done