#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/string.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/event.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace ftxui;

class Product {
public:
    std::string name;
    double price;
    std::string category;
    std::string description;
    int stock;

    Product(std::string n, double p, std::string cat, std::string desc, int s)
        : name(n), price(p), category(cat), description(desc), stock(s) {}

    std::string getDisplayInfo() const {
        std::stringstream ss;
        ss << name << " - " << std::fixed << std::setprecision(2) << price << " руб. (" 
           << (stock > 0 ? "В наличии: " + std::to_string(stock) : "Нет в наличии") << ")";
        return ss.str();
    }
};

class SportShopMenu {
private:
    std::vector<Product> products;
    std::vector<Product> cart;

    void initializeProducts() {
        // Беговые товары
        products.push_back(Product("Беговые кроссовки Nike", 8999.99, "Бег", "Профессиональные кроссовки для бега", 15));
        products.push_back(Product("Компрессионные леггинсы", 3499.50, "Бег", "Удобные леггинсы для бега", 20));
        
        // Велосипедные товары
        products.push_back(Product("Велосипедный шлем", 4599.00, "Велоспорт", "Защитный шлем для велосипедистов", 10));
        products.push_back(Product("Велосипедные перчатки", 1299.99, "Велоспорт", "Профессиональные перчатки", 25));
        
        // Товары для фитнеса
        products.push_back(Product("Коврик для йоги", 2199.00, "Фитнес", "Премиум коврик с противоскользящим покрытием", 30));
        products.push_back(Product("Гантели 5 кг (пара)", 3599.50, "Фитнес", "Профессиональные гантели", 15));
        
        // Зимние виды спорта
        products.push_back(Product("Лыжный костюм", 12999.99, "Зимний спорт", "Утепленный лыжный костюм", 8));
        products.push_back(Product("Сноуборд", 29999.00, "Зимний спорт", "Профессиональный сноуборд", 5));
    }

public:
    SportShopMenu() {
        initializeProducts();
    }

    Component createCatalogComponent() {
        // Создаем копию продуктов для безопасной работы
        std::vector<Product> available_products = products;
        
        // Вектор для отображения
        std::vector<std::string> product_entries;
        
        // Проверка на пустой каталог
        if (available_products.empty()) {
            product_entries.push_back("Товары отсутствуют");
        } else {
            for (const auto& product : available_products) {
                product_entries.push_back(product.name);
            }
        }

        // Защита от выхода за границы
        int selected_product = 0;
        
        // Создаем список с защитой от пустого списка
        auto product_list = Menu(
            &product_entries, 
            &selected_product, 
            MenuOption::Vertical()
        );

        // Создаем компонент с безопасной обработкой
        return Container::Vertical({
            product_list,
            Renderer([this, product_list, products = available_products, &selected_product](bool) {
                // Безопасное получение информации о товаре
                std::string details = products.empty() 
                    ? "Каталог пуст" 
                    : ("Цена: " + std::to_string(products[selected_product].price) + " руб.\n" +
                       "Категория: " + products[selected_product].category + "\n" +
                       "Описание: " + products[selected_product].description + "\n" +
                       "В наличии: " + std::to_string(products[selected_product].stock));

                return vbox({
                    text("Каталог спортивных товаров") | bold | center,
                    text("") | border,
                    hbox({
                        product_list->Render() | flex_grow,
                        text(" ") | border,
                        text(details) | border | flex_grow
                    }),
                    text("") | border,
                    text(products.empty() 
                        ? "Нет доступных товаров" 
                        : "↑↓ - выбор товара, Enter - добавить в корзину, Esc - выйти") | dim | center
                });
            }) | CatchEvent([this, products = available_products, &selected_product](Event event) {
                if (event == Event::Escape) {
                    return true;
                }
                
                // Добавление товара в корзину при нажатии Enter
                if (event == Event::Return && !products.empty()) {
                    if (products[selected_product].stock > 0) {
                        // Добавляем копию товара в корзину
                        cart.push_back(products[selected_product]);
                        
                        // Уменьшаем количество в исходном каталоге
                        for (auto& product : this->products) {
                            if (product.name == products[selected_product].name) {
                                product.stock--;
                                break;
                            }
                        }
                    }
                    return true;
                }
                return false;
            })
        });
    }

    Component createCartComponent() {
        std::vector<std::string> cart_entries;
        double total = 0.0;
        
        // Проверка на пустую корзину
        if (cart.empty()) {
            cart_entries.push_back("Корзина пуста");
        } else {
            for (const auto& item : cart) {
                cart_entries.push_back(item.getDisplayInfo());
                total += item.price;
            }
        }

        int selected_cart_item = 0;
        auto cart_list = Menu(&cart_entries, &selected_cart_item, MenuOption::Vertical());

        auto component = Container::Vertical({
            cart_list,
            Renderer([&] {
                return vbox({
                    text("Корзина покупок") | bold | center,
                    text(cart.empty() ? "Корзина пуста" : 
                         "Общая стоимость: " + std::to_string(total) + " руб.") | center,
                    text("") | border,
                    cart_list->Render(),
                    text("") | border,
                    text("Нажмите Esc для возврата") | dim | center
                });
            })
        });

        // Добавляем обработку событий для выхода
        component |= CatchEvent([&](Event event) {
            if (event == Event::Escape) {
                return true;
            }
            return false;
        });

        return component;
    }

    Component createPromotionsComponent() {
        auto component = Renderer([] {
            return vbox({
                text("Текущие акции") | bold | center,
                text("") | border,
                text("- Скидка 20% на зимние товары") | center,
                text("- При покупке беговых кроссовок - леггинсы в подарок") | center,
                text("") | border,
                text("Нажмите Esc для возврата") | dim | center
            });
        });

        // Добавляем обработку событий для выхода
        component |= CatchEvent([](Event event) {
            return event == Event::Escape;
        });

        return component;
    }

    static void Run() {
        SportShopMenu menu;
        auto screen = ScreenInteractive::Fullscreen();

        std::vector<std::string> menu_entries{
            "Каталог спортивных товаров",
            "Корзина покупок",
            "Текущие акции",
            "История заказов",
            "Личный кабинет",
            "Выход"
        };
        int selected = 0;
        auto main_menu = Menu(&menu_entries, &selected, MenuOption::Vertical());

        main_menu |= CatchEvent([&](Event event) {
            if (event == Event::Return) {
                switch(selected) {
                    case 0: {
                        auto catalog_component = menu.createCatalogComponent();
                        screen.Loop(catalog_component);
                        break;
                    }
                    case 1: {
                        auto cart_component = menu.createCartComponent();
                        screen.Loop(cart_component);
                        break;
                    }
                    case 2: {
                        auto promotions_component = menu.createPromotionsComponent();
                        screen.Loop(promotions_component);
                        break;
                    }
                    case 3: {
                        auto history_component = Renderer([] {
                            return vbox({
                                text("История заказов") | bold | center,
                                text("История заказов пока пуста") | center,
                                text("") | border,
                                text("Нажмите Esc для возврата") | dim | center
                            });
                        });
                        
                        // Добавляем обработку событий для выхода
                        history_component |= CatchEvent([](Event event) {
                            return event == Event::Escape;
                        });

                        screen.Loop(history_component);
                        break;
                    }
                    case 4: {
                        auto profile_component = Renderer([] {
                            return vbox({
                                text("Личный кабинет") | bold | center,
                                text("Личный кабинет недоступен") | center,
                                text("") | border,
                                text("Нажмите Esc для возврата") | dim | center
                            });
                        });
                        
                        // Добавляем обработку событий для выхода
                        profile_component |= CatchEvent([](Event event) {
                            return event == Event::Escape;
                        });

                        screen.Loop(profile_component);
                        break;
                    }
                    case 5: 
                        screen.Exit();
                        break;
                }
            }
            return false;
        });

        auto main_component = Container::Vertical({
            Renderer(main_menu, [&] {
                return vbox({
                    text("Спортивный Магазин") | bold | center,
                    text("Выберите раздел:") | center,
                    text("") | border,
                    main_menu->Render(),
                    text("") | border,
                    text("Навигация: ↑↓ Выбор, Enter - подтверждение") | dim | center
                });
            })
        });

        screen.Loop(main_component);
    }
};

int main() {
    try {
        SportShopMenu::Run();
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Неизвестная критическая ошибка" << std::endl;
        return 2;
    }
    return 0;
}
