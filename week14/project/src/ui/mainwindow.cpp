#include "mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
}

void MainWindow::setupUI() {
    setWindowTitle("Order Management System");
    resize(800, 600);

    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    setupUsersTab();
    setupOrdersTab();
    setupOrderStackTab();
}

void MainWindow::setupUsersTab() {
    QWidget *usersWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(usersWidget);

    usersTable = new QTableWidget();
    usersTable->setColumnCount(3);
    usersTable->setHorizontalHeaderLabels({"ID", "Name", "Type"});

    QPushButton *addUserBtn = new QPushButton("Add User");
    QPushButton *addCustomerBtn = new QPushButton("Add Customer");
    QPushButton *addEmployeeBtn = new QPushButton("Add Employee");
    QPushButton *deleteUserBtn = new QPushButton("Delete User");

    connect(addUserBtn, &QPushButton::clicked, this, &MainWindow::addUser);
    connect(addCustomerBtn, &QPushButton::clicked, this, &MainWindow::addCustomer);
    connect(addEmployeeBtn, &QPushButton::clicked, this, &MainWindow::addEmployee);
    connect(deleteUserBtn, &QPushButton::clicked, this, &MainWindow::deleteUser);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(addUserBtn);
    btnLayout->addWidget(addCustomerBtn);
    btnLayout->addWidget(addEmployeeBtn);
    btnLayout->addWidget(deleteUserBtn);

    layout->addWidget(usersTable);
    layout->addLayout(btnLayout);

    tabWidget->addTab(usersWidget, "Users");
}

void MainWindow::setupOrdersTab() {
    QWidget *ordersWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(ordersWidget);

    ordersTable = new QTableWidget();
    ordersTable->setColumnCount(3);
    ordersTable->setHorizontalHeaderLabels({"Order ID", "Total Cost", "Items Count"});

    QPushButton *addOrderBtn = new QPushButton("Add Order");
    QPushButton *deleteOrderBtn = new QPushButton("Delete Order");
    QPushButton *processOrderBtn = new QPushButton("Process Order");

    connect(addOrderBtn, &QPushButton::clicked, this, &MainWindow::addOrder);
    connect(deleteOrderBtn, &QPushButton::clicked, this, &MainWindow::deleteOrder);
    connect(processOrderBtn, &QPushButton::clicked, this, &MainWindow::processOrder);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(addOrderBtn);
    btnLayout->addWidget(deleteOrderBtn);
    btnLayout->addWidget(processOrderBtn);

    layout->addWidget(ordersTable);
    layout->addLayout(btnLayout);

    tabWidget->addTab(ordersWidget, "Orders");
}

void MainWindow::setupOrderStackTab() {
    QWidget *orderStackWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(orderStackWidget);

    orderStackTable = new QTableWidget();
    orderStackTable->setColumnCount(3);
    orderStackTable->setHorizontalHeaderLabels({"Order ID", "Total Cost", "Items Count"});

    pushToStackBtn = new QPushButton("Push Order to Stack");
    popFromStackBtn = new QPushButton("Pop Order from Stack");
    viewTopStackBtn = new QPushButton("View Top Order");

    connect(pushToStackBtn, &QPushButton::clicked, this, &MainWindow::pushToOrderStack);
    connect(popFromStackBtn, &QPushButton::clicked, this, &MainWindow::popFromOrderStack);
    connect(viewTopStackBtn, &QPushButton::clicked, this, &MainWindow::viewTopOrderStack);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(pushToStackBtn);
    btnLayout->addWidget(popFromStackBtn);
    btnLayout->addWidget(viewTopStackBtn);

    layout->addWidget(orderStackTable);
    layout->addLayout(btnLayout);

    tabWidget->addTab(orderStackWidget, "Order Stack");
}

void MainWindow::updateUsersTable() {
    usersTable->setRowCount(0);
    for (const auto& user : users) {
        int row = usersTable->rowCount();
        usersTable->insertRow(row);
        // Заполнение данными
    }
}

void MainWindow::updateOrdersTable() {
    ordersTable->setRowCount(0);
    for (const auto& order : orders) {
        int row = ordersTable->rowCount();
        ordersTable->insertRow(row);
        // Заполнение данными
    }
}

void MainWindow::pushToOrderStack() {
    if (!orders.empty()) {
        auto order = orders.back();
        orderStack.push(order);
        updateOrderStackTable();
        QMessageBox::information(this, "Stack Operation", "Order pushed to stack successfully!");
    } else {
        QMessageBox::warning(this, "Stack Operation", "No orders available to push!");
    }
}

void MainWindow::popFromOrderStack() {
    if (!orderStack.empty()) {
        orderStack.pop();
        updateOrderStackTable();
        QMessageBox::information(this, "Stack Operation", "Order popped from stack successfully!");
    } else {
        QMessageBox::warning(this, "Stack Operation", "Order stack is empty!");
    }
}

void MainWindow::viewTopOrderStack() {
    if (!orderStack.empty()) {
        auto topOrder = orderStack.top();
        QString message = QString("Top Order ID: %1\nTotal Cost: %2")
            .arg(QString::fromStdString(topOrder->getOrderID()))
            .arg(topOrder->getTotalCost());
        QMessageBox::information(this, "Top Order", message);
    } else {
        QMessageBox::warning(this, "Stack Operation", "Order stack is empty!");
    }
}

void MainWindow::updateOrderStackTable() {
    orderStackTable->setRowCount(0);
    
    std::vector<std::shared_ptr<Order>> tempStack;
    while (!orderStack.empty()) {
        tempStack.push_back(orderStack.top());
        orderStack.pop();
    }

    for (auto it = tempStack.rbegin(); it != tempStack.rend(); ++it) {
        int row = orderStackTable->rowCount();
        orderStackTable->insertRow(row);
        
        orderStackTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString((*it)->getOrderID())));
        orderStackTable->setItem(row, 1, new QTableWidgetItem(QString::number((*it)->getTotalCost())));
        orderStackTable->setItem(row, 2, new QTableWidgetItem(QString::number((*it)->getItems().size())));
        
        orderStack.push(*it);
    }
}

// Заглушки для остальных методов
void MainWindow::addUser() {}
void MainWindow::addCustomer() {}
void MainWindow::addEmployee() {}
void MainWindow::addOrder() {}
void MainWindow::deleteUser() {}
void MainWindow::deleteOrder() {}
void MainWindow::processOrder() {}