#include <iostream>
#include <thread>
#include <chrono>

class TrafficLight {
private:
    bool isGreen;

public:
    TrafficLight() : isGreen(false) {}

    void setGreen() {
        isGreen = true;
    }

    void setRed() {
        isGreen = false;
    }

    bool isSignalGreen() const {
        return isGreen;
    }
};

class TrafficManagementSystem {
private:
    TrafficLight trafficLight;

public:
    void manageTraffic() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(5)); // Green for 5 seconds
            trafficLight.setRed();
            std::cout << "Traffic light turned RED" << std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(3)); // Red for 3 seconds
            trafficLight.setGreen();
            std::cout << "Traffic light turned GREEN" << std::endl;
        }
    }
};

int main() {
    TrafficManagementSystem system;

    std::thread trafficThread(&TrafficManagementSystem::manageTraffic, &system);

    // Simulate other operations in the main thread
    for (int i = 0; i < 10; ++i) {
        std::cout << "Vehicle " << i + 1 << " is crossing" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    trafficThread.join();

    return 0;
}
