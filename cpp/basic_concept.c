int n, count;
mutex_t mtx;

void TProduce() {
    while (1) {
        mutex_lock(mtx);
        while (!(n != count)) {
            mutex_unlock_and_sleep(mtx);
            mutex_lock(mtx);
        }
        // do something
        count++;
        wakeup();
        mutex_unlock(mtx);
    }
}

void TConsume() {
    while (1) {
        mutex_lock(mtx);
        while (!(n != 0)) {
            mutex_unlock_and_sleep(mtx);
            mutex_lock(mtx);
        }
        // do something
        count--;
        wakeup();
        mutex_unlock(mtx);
    }
}

int main() {
    create_thread(TConsume);
    create_thread(TProduce);
    join();
}
