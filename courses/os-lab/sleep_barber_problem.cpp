const int n = 100;

class sleep_barber_problem {
  private:
    enum barber_status { asleep, conscious };
    enum barber_chair_status { idle, busy };

    const int number_of_chairs = n;
    int customers_waiting[n];
    int number_of_customers = 0;
    barber_status barber = asleep;
    barber_chair_status barber_chair = idle;
    int current_customer_on_barber_chair = 0;

  public:
    void in_customer(int customer_id);
};

void sleep_barber_problem::in_customer(int customer_id) {
    int my_index;
    do {
        if (number_of_customers >= n) {
            // Customer leaves if all chairs are occupied.
            return;
        } else if (number_of_customers == 0) {
            // Store my index in queue
            my_index = number_of_customers - 1;
            customers_waiting[number_of_customers++] = customer_id;
            // Wake up the barber
            barber = conscious;
        } else if (number_of_customers < number_of_chairs) {
            // Store my index in queue
            my_index = number_of_customers - 1;
            customers_waiting[number_of_customers++] = customer_id;
        }

        while (barber_chair == busy)
            ; // Wait until the chair is idle.
        int j = current_customer_on_barber_chair;
        while (j !=
               (current_customer_on_barber_chair + number_of_customers - 1) %
                   n) {
            if (j != my_index + (n - 1) % n) {
                // Wait until previous customer in the queue before me is
                // served.
                j = current_customer_on_barber_chair;
            } else if (barber_chair == idle) {
                // Go to barber room when chair is idle.
                j = (j + 1) % n;
                break;
            }
        }

        // Action on barber chair
        barber_chair = busy;
        current_customer_on_barber_chair = customer_id;

        // Actions on barber chair

        // Exit barber room
        barber_chair = idle;
        if (--number_of_customers == 0)
            barber = asleep;
    } while (true);
}

void sleep_barber_problem() {
    class sleep_barber_problem sbp;
    return;
}
