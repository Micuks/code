const int n = 100;
typedef int semaphore;

class sleep_barber_problem {
  private:
    const int num_waiting_chairs = n;
    int free_waiting_chairs = 0;
    semaphore waiting_chair_mutex = 0;
    semaphore barber_ready = 0;
    semaphore customer_ready = 0;
    void wait(semaphore sem);
    void signal(semaphore sem);

  public:
    void customer();
    void barber();
};

void sleep_barber_problem::barber() {
    signal(barber_ready);
    wait(customer_ready);

    // Cut customer's hair
}

void sleep_barber_problem::customer() {
    wait(waiting_chair_mutex);
    if (free_waiting_chairs <= 0) {
        // No free waiting chair, exit barber shop.
        // Release waiting chairs mutex
        signal(waiting_chair_mutex);
    } else {
        free_waiting_chairs--;
        signal(free_waiting_chairs);

        wait(barber_ready);

        // Release the waiting chair occupied by the customer.
        wait(waiting_chair_mutex);
        free_waiting_chairs++;
        signal(waiting_chair_mutex);

        signal(customer_ready);

        // Get customer's hair cut

        // Exit barber shop
    }
}
