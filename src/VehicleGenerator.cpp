#include "header/VehicleGenerator.hpp"
#include "header/VehicleClass.hpp"
#include "header/Route.hpp"
#include "header/Lane.hpp"

VehicleGenerator::VehicleGenerator() 
    : nextId(1), spawnInterval(0.8f) {
}

void VehicleGenerator::update(std::vector<Vehicle>& vehicles, float deltaTime) {
    if (spawnClock.getElapsedTime().asSeconds() >= spawnInterval) {
        float gap = 20.0f;
        int a2Count = 0, a3Count = 0, d2Count = 0, d3Count = 0, b2Count = 0, b3Count = 0, c2Count = 0, c3Count = 0;
        for (const auto& v : vehicles) {
            if (v.getOriginLane() == Lane::A2) a2Count++;
            if (v.getOriginLane() == Lane::A3) a3Count++;
            if (v.getOriginLane() == Lane::D2) d2Count++;
            if (v.getOriginLane() == Lane::D3) d3Count++;
            if (v.getOriginLane() == Lane::B2) b2Count++;
            if (v.getOriginLane() == Lane::B3) b3Count++;
            if (v.getOriginLane() == Lane::C2) c2Count++;
            if (v.getOriginLane() == Lane::C3) c3Count++;
        }

        int laneChoice = rand() % 8;
        switch (laneChoice) {
            case 0:
                {
                    int routeChoice = rand() % 3;
                    switch (routeChoice) {
                        case 0:
                            vehicles.emplace_back(nextId++, Lane::A2, Lane::B1, Route::MOVE_A_TO_B, static_cast<float>(a2Count));
                            vehicles.back().move(sf::Vector2f(552.5, -gap * a2Count));
                            break;
                        case 1:
                            vehicles.emplace_back(nextId++, Lane::A2, Lane::D1, Route::MOVE_A_TO_D, static_cast<float>(a2Count));
                            vehicles.back().move(sf::Vector2f(552.5, -gap * a2Count));
                            break;
                        case 2:
                            vehicles.emplace_back(nextId++, Lane::A2, Lane::C1, Route::MOVE_A_TO_C, static_cast<float>(a2Count));
                            vehicles.back().move(sf::Vector2f(590, -gap * a2Count));
                            break;
                    }
                }
                break;
            case 1:
                {
                    int routeChoice = rand() % 3;
                    switch (routeChoice) {
                        case 0:
                            vehicles.emplace_back(nextId++, Lane::A3, Lane::B1, Route::MOVE_A_TO_B, static_cast<float>(a3Count));
                            vehicles.back().move(sf::Vector2f(552.5, -gap * a3Count));
                            break;
                        case 1:
                            vehicles.emplace_back(nextId++, Lane::A3, Lane::D1, Route::MOVE_A_TO_D, static_cast<float>(a3Count));
                            vehicles.back().move(sf::Vector2f(552.5, -gap * a3Count));
                            break;
                        case 2:
                            vehicles.emplace_back(nextId++, Lane::A3, Lane::C1, Route::MOVE_A_TO_C, static_cast<float>(a3Count));
                            vehicles.back().move(sf::Vector2f(590, -gap * a3Count));
                            break;
                    }
                }
                break;
            case 2:
                {
                    int routeChoice = rand() % 3;
                    switch (routeChoice) {
                        case 0:
                            vehicles.emplace_back(nextId++, Lane::D2, Lane::C1, Route::MOVE_D_TO_C, static_cast<float>(d2Count));
                            vehicles.back().move(sf::Vector2f(-gap * d2Count, 485.5));
                            break;
                        case 1:
                            vehicles.emplace_back(nextId++, Lane::D2, Lane::B1, Route::MOVE_D_TO_B, static_cast<float>(d2Count));
                            vehicles.back().move(sf::Vector2f(-gap * d2Count, 485.5));
                            break;
                        case 2:
                            vehicles.emplace_back(nextId++, Lane::D2, Lane::A1, Route::MOVE_D_TO_A, static_cast<float>(d2Count));
                            vehicles.back().move(sf::Vector2f(-gap * d2Count, 445.5));
                            break;
                    }
                }
                break;
            case 3:
                {
                    int routeChoice = rand() % 3;
                    switch (routeChoice) {
                        case 0:
                            vehicles.emplace_back(nextId++, Lane::D3, Lane::C1, Route::MOVE_D_TO_C, static_cast<float>(d3Count));
                            vehicles.back().move(sf::Vector2f(-gap * d3Count, 485.5));
                            break;
                        case 1:
                            vehicles.emplace_back(nextId++, Lane::D3, Lane::B1, Route::MOVE_D_TO_B, static_cast<float>(d3Count));
                            vehicles.back().move(sf::Vector2f(-gap * d3Count, 485.5));
                            break;
                        case 2:
                            vehicles.emplace_back(nextId++, Lane::D3, Lane::A1, Route::MOVE_D_TO_A, static_cast<float>(d3Count));
                            vehicles.back().move(sf::Vector2f(-gap * d3Count, 445.5));
                            break;
                    }
                }
                break;
            case 4:
                {
                    int routeChoice = rand() % 3;
                    switch (routeChoice) {
                        case 0:
                            vehicles.emplace_back(nextId++, Lane::B2, Lane::A1, Route::MOVE_B_TO_A, static_cast<float>(b2Count));
                            vehicles.back().move(sf::Vector2f(512.5, 1080 + gap * b2Count));
                            break;
                        case 1:
                            vehicles.emplace_back(nextId++, Lane::B2, Lane::C1, Route::MOVE_B_TO_C, static_cast<float>(b2Count));
                            vehicles.back().move(sf::Vector2f(512.5, 1080 + gap * b2Count));
                            break;
                        case 2:
                            vehicles.emplace_back(nextId++, Lane::B2, Lane::D1, Route::MOVE_B_TO_D, static_cast<float>(b2Count));
                            vehicles.back().move(sf::Vector2f(474.5, 1080 + gap * b2Count));
                            break;
                    }
                }
                break;
            case 5:
                {
                    int routeChoice = rand() % 3;
                    switch (routeChoice) {
                        case 0:
                            vehicles.emplace_back(nextId++, Lane::B3, Lane::A1, Route::MOVE_B_TO_A, static_cast<float>(b3Count));
                            vehicles.back().move(sf::Vector2f(512.5, 1080 + gap * b3Count));
                            break;
                        case 1:
                            vehicles.emplace_back(nextId++, Lane::B3, Lane::C1, Route::MOVE_B_TO_C, static_cast<float>(b3Count));
                            vehicles.back().move(sf::Vector2f(512.5, 1080 + gap * b3Count));
                            break;
                        case 2:
                            vehicles.emplace_back(nextId++, Lane::B3, Lane::D1, Route::MOVE_B_TO_D, static_cast<float>(b3Count));
                            vehicles.back().move(sf::Vector2f(474.5, 1080 + gap * b3Count));
                            break;
                    }
                }
                break;
            case 6:
                {
                    int routeChoice = rand() % 3;
                    switch (routeChoice) {
                        case 0:
                            vehicles.emplace_back(nextId++, Lane::C2, Lane::B1, Route::MOVE_C_TO_B, static_cast<float>(c2Count));
                            vehicles.back().move(sf::Vector2f(1080 + gap * c2Count, 562.5));
                            break;
                        case 1:
                            vehicles.emplace_back(nextId++, Lane::C2, Lane::D1, Route::MOVE_C_TO_D, static_cast<float>(c2Count));
                            vehicles.back().move(sf::Vector2f(1080 + gap * c2Count, 523.5));
                            break;
                        case 2:
                            vehicles.emplace_back(nextId++, Lane::C2, Lane::A1, Route::MOVE_C_TO_A, static_cast<float>(c2Count));
                            vehicles.back().move(sf::Vector2f(1080 + gap * c2Count, 523.5));
                            break;
                    }
                }
                break;
            case 7:
                {
                    int routeChoice = rand() % 3;
                    switch (routeChoice) {
                        case 0:
                            vehicles.emplace_back(nextId++, Lane::C3, Lane::B1, Route::MOVE_C_TO_B, static_cast<float>(c3Count));
                            vehicles.back().move(sf::Vector2f(1080 + gap * c3Count, 562.5));
                            break;
                        case 1:
                            vehicles.emplace_back(nextId++, Lane::C3, Lane::D1, Route::MOVE_C_TO_D, static_cast<float>(c3Count));
                            vehicles.back().move(sf::Vector2f(1080 + gap * c3Count, 523.5));
                            break;
                        case 2:
                            vehicles.emplace_back(nextId++, Lane::C3, Lane::A1, Route::MOVE_C_TO_A, static_cast<float>(c3Count));
                            vehicles.back().move(sf::Vector2f(1080 + gap * c3Count, 523.5));
                            break;
                    }
                }
                break;
        }
        int lane = rand() % 8;
        switch (lane) {
            case 0:
                {
                    int routeChoice = rand() % 3;
                    switch (routeChoice) {
                        case 0:
                            vehicles.emplace_back(nextId++, Lane::D2, Lane::C1, Route::MOVE_D_TO_C, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(-gap * (vehicles.size() % 5), 485.5));
                            break;
                        case 1:
                            vehicles.emplace_back(nextId++, Lane::D2, Lane::B1, Route::MOVE_D_TO_B, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(-gap * (vehicles.size() % 5), 485.5));
                            break;
                        case 2:
                            vehicles.emplace_back(nextId++, Lane::D2, Lane::A1, Route::MOVE_D_TO_A, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(-gap * (vehicles.size() % 5), 445.5));
                            break;
                    }
                }
                break;
            case 1:
                {
                    int routeChoice = rand() % 3;
                    switch (routeChoice) {
                        case 0:
                            vehicles.emplace_back(nextId++, Lane::D3, Lane::C1, Route::MOVE_D_TO_C, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(-gap * (vehicles.size() % 5), 485.5));
                            break;
                        case 1:
                            vehicles.emplace_back(nextId++, Lane::D3, Lane::B1, Route::MOVE_D_TO_B, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(-gap * (vehicles.size() % 5), 485.5));
                            break;
                        case 2:
                            vehicles.emplace_back(nextId++, Lane::D3, Lane::A1, Route::MOVE_D_TO_A, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(-gap * (vehicles.size() % 5), 445.5));
                            break;
                    }
                }
                break;
            case 2:
                {
                    int routeChoice = rand() % 3;
                    switch (routeChoice) {
                        case 0:
                            vehicles.emplace_back(nextId++, Lane::A2, Lane::B1, Route::MOVE_A_TO_B, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(552.5, -gap * (vehicles.size() % 5)));
                            break;
                        case 1:
                            vehicles.emplace_back(nextId++, Lane::A2, Lane::D1, Route::MOVE_A_TO_D, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(552.5, -gap * (vehicles.size() % 5)));
                            break;
                        case 2:
                            vehicles.emplace_back(nextId++, Lane::A2, Lane::C1, Route::MOVE_A_TO_C, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(590, -gap * (vehicles.size() % 5)));
                            break;
                    }
                }
                break;
            case 3:
                {
                    int routeChoice = rand() % 3;
                    switch (routeChoice) {
                        case 0:
                            vehicles.emplace_back(nextId++, Lane::A3, Lane::B1, Route::MOVE_A_TO_B, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(552.5, -gap * (vehicles.size() % 5)));
                            break;
                        case 1:
                            vehicles.emplace_back(nextId++, Lane::A3, Lane::D1, Route::MOVE_A_TO_D, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(552.5, -gap * (vehicles.size() % 5)));
                            break;
                        case 2:
                            vehicles.emplace_back(nextId++, Lane::A3, Lane::C1, Route::MOVE_A_TO_C, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(590, -gap * (vehicles.size() % 5)));
                            break;
                    }
                }
                break;
            case 4:
                {
                    int routeChoice = rand() % 3;
                    switch (routeChoice) {
                        case 0:
                            vehicles.emplace_back(nextId++, Lane::C2, Lane::B1, Route::MOVE_C_TO_B, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(1080 + gap * (vehicles.size() % 5), 562.5));
                            break;
                        case 1:
                            vehicles.emplace_back(nextId++, Lane::C2, Lane::D1, Route::MOVE_C_TO_D, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(1080 + gap * (vehicles.size() % 5), 523.5));
                            break;
                        case 2:
                            vehicles.emplace_back(nextId++, Lane::C2, Lane::A1, Route::MOVE_C_TO_A, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(1080 + gap * (vehicles.size() % 5), 523.5));
                            break;
                    }
                }
                break;
            case 5:
                {
                    int routeChoice = rand() % 3;
                    switch (routeChoice) {
                        case 0:
                            vehicles.emplace_back(nextId++, Lane::C3, Lane::B1, Route::MOVE_C_TO_B, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(1080 + gap * (vehicles.size() % 5), 562.5));
                            break;
                        case 1:
                            vehicles.emplace_back(nextId++, Lane::C3, Lane::D1, Route::MOVE_C_TO_D, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(1080 + gap * (vehicles.size() % 5), 523.5));
                            break;
                        case 2:
                            vehicles.emplace_back(nextId++, Lane::C3, Lane::A1, Route::MOVE_C_TO_A, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(1080 + gap * (vehicles.size() % 5), 523.5));
                            break;
                    }
                }
                break;
            case 6:
                {
                    int routeChoice = rand() % 3;
                    switch (routeChoice) {
                        case 0:
                            vehicles.emplace_back(nextId++, Lane::B2, Lane::A1, Route::MOVE_B_TO_A, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(512.5, 1080 + gap * (vehicles.size() % 5)));
                            break;
                        case 1:
                            vehicles.emplace_back(nextId++, Lane::B2, Lane::C1, Route::MOVE_B_TO_C, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(512.5, 1080 + gap * (vehicles.size() % 5)));
                            break;
                        case 2:
                            vehicles.emplace_back(nextId++, Lane::B2, Lane::D1, Route::MOVE_B_TO_D, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(474.5, 1080 + gap * (vehicles.size() % 5)));
                            break;
                    }
                }
                break;
            case 7:
                {
                    int routeChoice = rand() % 3;
                    switch (routeChoice) {
                        case 0:
                            vehicles.emplace_back(nextId++, Lane::B3, Lane::A1, Route::MOVE_B_TO_A, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(512.5, 1080 + gap * (vehicles.size() % 5)));
                            break;
                        case 1:
                            vehicles.emplace_back(nextId++, Lane::B3, Lane::C1, Route::MOVE_B_TO_C, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(512.5, 1080 + gap * (vehicles.size() % 5)));
                            break;
                        case 2:
                            vehicles.emplace_back(nextId++, Lane::B3, Lane::D1, Route::MOVE_B_TO_D, static_cast<float>(vehicles.size() % 5));
                            vehicles.back().move(sf::Vector2f(474.5, 1080 + gap * (vehicles.size() % 5)));
                            break;
                    }
                }
                break;
        }
        spawnClock.restart();
    }
}