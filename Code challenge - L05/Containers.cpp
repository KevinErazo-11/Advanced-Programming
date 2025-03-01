#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <vector>

void displayInventory(const std::map<std::string, int>& inventory) {
    std::cout << "Current Inventory:\n";
    for (const auto& item : inventory) {
        std::cout<< "\t" << item.first << ": " << item.second << " in stock\n";
    }
    std::cout << std::endl;
}

void addProduct(std::map<std::string, int>& inventory, const std::string& product, int quantity) {
    if (inventory.find(product) != inventory.end()){
        std::cout<<product<< " already exists in the inventory. Use update option instead. \n";
    } else{
        inventory[product] = quantity;
        std::cout << product << " added with quantity: " << quantity << "\n.";
    }
}

void updateProduct(std::map<std::string, int>& inventory, const std::string& product, int quantity){
    if(inventory.find(product) != inventory.end()){
        inventory[product] = quantity;
        std::cout<< product<< " updated to quantity: " << quantity << "\n";
    }else{
        std::cout << product << " does not exist in the inventory. Use add option instead. \n";
    }
}

void addCategory(std::set<std::string>& categories, const std::string& category) {
    categories.insert(category);
    std::cout << "Category '" << category << "' added successfully.\n";
}

void displayCategories(const std::set<std::string>& categories) {
    std::cout << "Product Categories:\n";
    for (const auto& category : categories) {
        std::cout << "- " << category << "\n";
    }
}

void addOrder(std::queue<std::string>& orders, const std::string& order) {
    orders.push(order);
    std::cout << "Order added: " << order << "\n";
}

void processOrder(std::queue<std::string>& orders) {
    if (!orders.empty()) {
        std::cout << "Processing " << orders.front() << "\n";
        orders.pop();
    } else {
        std::cout << "No orders to process.\n";
    }
}

void addRestock(std::stack<std::pair<std::string, int>>& restocks, const std::string& product, int quantity) {
    restocks.push({product, quantity});
    std::cout << "Restock batch added: " << quantity << " units of " << product << "\n";
}

void processRestock(std::stack<std::pair<std::string, int>>& restocks) {
    if (!restocks.empty()) {
        auto item = restocks.top();
        std::cout << "Restocking " << item.second << " units of " << item.first << "\n";
        restocks.pop();
    } else {
        std::cout << "No restock batches to process.\n";
    }
}

void addToCart(std::vector<std::string>& cart, const std::string& product) {
    cart.push_back(product);
    std::cout << product << " added to cart.\n";
}

void displayCart(const std::vector<std::string>& cart) {
    std::cout << "Items in customer cart:\n";
    for (const auto& item : cart) {
        std::cout << "- " << item << "\n";
    }
}

int main() {
    std::map<std::string, int> inventory;
    std::set<std::string> productCategories;
    std::queue<std::string> orders;
    std::stack<std::pair<std::string, int>> restocks;
    std::vector<std::string> customerCart;

    // Adding products
    inventory["Laptop"] = 5;
    inventory["Mouse"] = 20;
    inventory["Keyboard"] = 10;

    // Adding default categories
    productCategories.insert("Electronics");
    productCategories.insert("Accessories");
    productCategories.insert("Peripherals");

    int choice;
    std::string product;
    int quantity;
    std::string category;
    std::string order;

    do {
        std::cout << "\nInventory Management System\n";
        std::cout << "\t1. Display inventory\n";
        std::cout << "\t2. Add new product\n";
        std::cout << "\t3. Update product quantity \n";
        std::cout << "\t4. Add new category\n";
        std::cout << "\t5. Display categories\n";
        std::cout << "\t6. Add new order\n";
        std::cout << "\t7. Process order\n";
        std::cout << "\t8. Add restock batch\n";
        std::cout << "\t9. Process restock batch\n";
        std::cout << "\t10. Add to cart\n";
        std::cout << "\t11. Display cart\n";
        std::cout << "\t12. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch(choice){
            case 1:
                displayInventory(inventory);
                break;
            case 2:
                std::cout << "Enter product name: ";
                std::cin >> product;
                std::cout << "Enter quantity: ";
                std::cin >> quantity;
                addProduct(inventory, product, quantity);
                break;
            case 3:
                std::cout << "Enter product name: ";
                std::cin >> product;
                std::cout << "Enter new quantity: ";
                std::cin >> quantity;
                updateProduct(inventory, product, quantity);
                break;
            case 4:
                std::cout << "Enter category name: ";
                std::cin >> category;
                addCategory(productCategories, category);
                break;
            case 5:
                displayCategories(productCategories);
                break;
            case 6:
                std::cout << "Enter order details: ";
                std::cin.ignore();
                std::getline(std::cin, order);
                addOrder(orders, order);
                break;
            case 7:
                processOrder(orders);
                break;
            case 8:
                std::cout << "Enter product name: ";
                std::cin >> product;
                std::cout << "Enter quantity: ";
                std::cin >> quantity;
                addRestock(restocks, product, quantity);
                break;
            case 9:
                processRestock(restocks);
                break;
            case 10:
                std::cout << "Enter product name: ";
                std::cin >> product;
                addToCart(customerCart, product);
                break;
            case 11:
                displayCart(customerCart);
                break;
            case 12:
                std::cout << "Exiting... \n";
                break;
            default:
                std::cout << "Invalid choice. Please, try again. \n";
        }
    }while(choice != 12);

    return 0;
}