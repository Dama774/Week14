#include <iostream>
#include <memory>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/string.hpp>
#include "../headers/user.h"
#include "../headers/employee.h"
#include "../headers/customer.h"
#include "../headers/client.h"
#include "../headers/item.h"
#include "../headers/order.h"

using namespace ftxui;

int main() {
    // Пример использования FTXUI для создания простого интерфейса
    auto document = vbox({
        text("Система управления заказами") | bold | center,
        text("------------------------------") | dim,
        text("Добро пожаловать!") | color(Color::Blue),
    });

    // Настройка экрана
    auto screen = Screen::Create(
        Dimension::Full(),       // Полная ширина
        Dimension::Fit(document) // Высота по содержимому
    );

    // Рендеринг
    Render(screen, document);
    screen.Print();

    // Создание товаров
    auto item1 = std::make_shared<Item>("Футболка", 1500.0, 2);
    auto item2 = std::make_shared<Item>("Кроссовки", 5000.0, 1);

    // Создание заказа
    auto order = std::make_shared<Order>("ORD-001");
    order->addItem(item1);
    order->addItem(item2);

    // Создание клиента
    Client client("Иван Петров", "USER-001", "CLIENT-001");

    // Размещение и обработка заказа
    client.placeOrder(order);
    client.makePayment(order);
    client.processOrder(order);

    // Вывод информации о заказе
    std::cout << "Заказ " << order->getOrderID() << std::endl;
    std::cout << "Общая стоимость: " << order->getTotalCost() << " руб." << std::endl;

    for (const auto& item : order->getItems()) {
        std::cout << "Товар: " << item->getName() 
                  << ", Цена: " << item->getPrice() 
                  << ", Количество: " << item->getQuantity() << std::endl;
    }

    return 0;
}
