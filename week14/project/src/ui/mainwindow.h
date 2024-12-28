#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <vector>
#include <memory>
#include <stack>
#include "../models/user.h"
#include "../models/order.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    // Существующие методы
    void addUser();
    void addCustomer();
    void addEmployee();
    void addOrder();
    void deleteUser();
    void deleteOrder();
    void processOrder();

    // Новые методы для работы со стеком заказов
    void pushToOrderStack();
    void popFromOrderStack();
    void viewTopOrderStack();

private:
    // Существующие элементы интерфейса
    QTabWidget *tabWidget;
    QTableWidget *usersTable;
    QTableWidget *ordersTable;
    std::vector<std::shared_ptr<User>> users;
    std::vector<std::shared_ptr<Order>> orders;

    // Новые элементы для стека заказов
    std::stack<std::shared_ptr<Order>> orderStack;
    QTableWidget *orderStackTable;
    QPushButton *pushToStackBtn;
    QPushButton *popFromStackBtn;
    QPushButton *viewTopStackBtn;

    // Существующие методы настройки интерфейса
    void setupUI();
    void setupUsersTab();
    void setupOrdersTab();
    
    // Новый метод для настройки вкладки стека заказов
    void setupOrderStackTab();

    // Существующие методы обновления таблиц
    void updateUsersTable();
    void updateOrdersTable();
    
    // Новый метод обновления таблицы стека заказов
    void updateOrderStackTable();
};

#endif // MAINWINDOW_H