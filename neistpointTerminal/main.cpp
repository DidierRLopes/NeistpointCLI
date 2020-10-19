/* *************************************************************************************** //
 //                                                                                        //
 //  main.cpp                                                                          //
 //  neistpointTerminal                                                                    //
 //                                                                                        //
 //  Created by Didier Rodrigues Lopes on 2019.                                            //
 //  Copyright © 2019 Didier Lopes. All rights reserved.                                   //
 //                                                                                        //
 // *************************************************************************************** */


#include <iostream>
#include <fstream>
#include <sstream>

#include "database.h"


// Print flow of action, for better understanding
void print_flow(void)
{
    std::cout << "\n\n";
    std::cout << "                  (request_material())                  \n";
    std::cout << "request_product() ------------------->   [materialToRequest] \n";
    std::cout << "                      |                           | \n";
    std::cout << "                      |                           |  order_material()  \n";
    std::cout << "                      |                           V \n";
    std::cout << "                      |                   [materialShipping]    \n";
    std::cout << "                      |                           | \n";
    std::cout << "                      |                           |  arrived_material()  \n";
    std::cout << "                      |                           V \n";
    std::cout << "                      |                   [materialInStock]  ----  \n";
    std::cout << "                      |                                         | \n";
    std::cout << "                      |                                         | \n";
    std::cout << "                      ----------------->  [productToCreate]     | \n";
    std::cout << "                     (request_product())          |             V \n";
    std::cout << "                                                  |  order_product()  \n";
    std::cout << "                                                  V \n";
    std::cout << "                                           [productCreating]    \n";
    std::cout << "                                                  | \n";
    std::cout << "                                                  |  arrived_product()  \n";
    std::cout << "                                                  V \n";
    std::cout << "                                            [productInStock]    \n";
    std::cout << "                                                  | \n";
    std::cout << "                                                  |  sent_product()  \n";
    std::cout << "                                                  V \n";
    std::cout << "                                              [productSent]    \n";
    
    std::cout << "\n\n";
}

int main() {
    Database db;
    db.load_database();
    
    std::cout << BOLD(SUCCESS("\n\nWelcome to Neist Point Management Database!\n"));
    std::cout << ERROR("17 - See program flow\n\n");
    
    int val;
    do
    {
        std::cout << BOLD(ACTION("1 - New Product request from costumer\n\n"));
        // +productToCreate, and +materialToRequest if the material is not in stock
        
        std::cout << BOLD(ACTION("2 - Add Material to be requested\n"));
        // +materialToRequest
        
        std::cout << INFO("3 - See Materials to be requested\n");
        
        std::cout << BOLD(ACTION("4 - Add Product to be created\n"));
        // +productToCreate
        
        std::cout << INFO("5 - See Products to be created\n\n");
        
        
        std::cout << BOLD(ACTION("6 - Order Material\n")); //give chance to do all at once from previous mat
        // -materialToRequest, +materialShipping
        
        std::cout << INFO("7 - See Materials being shipped\n");
        
        std::cout << BOLD(ACTION("8 - Confirm Material has arrived\n")); //give chance to do all at once from previous mat
        // +materialInStock, -materialShipping
        
        std::cout << INFO("9 - See Materials in stock\n");
        
        std::cout << INFO("10 - See possible products to be created from material stock\n\n");
        
        std::cout << BOLD(ACTION("11 - Order Products from Material stock\n"));
        //-materialInStock, +productCreating
        
        std::cout << INFO("12 - See Products being created and shipped\n");
        
        std::cout << BOLD(ACTION("13 - Confirm Product has arrived\n")); //give chance to do all at once from previous mat
        //+productInStock, -productCreating
        
        std::cout << INFO("14 - See Products in stock\n");
        
        std::cout << BOLD(ACTION("15 - Product is dispatched\n")); //give chance to do all at once from previous mat
        //-productInStock, +productSold
        
        std::cout << INFO("16 - See Products Sent\n\n");
        
        std::cout << BOLD(NORMAL("What can I do for you today? (0 - EXIT and SAVE)\n"));
        std::cin >> val;
        
        switch(val)
        {
            case 1: db.request_productCustomer();
                break;
            case 2: db.request_material();
                break;
            case 3: db.print_matrix(MATERIAL_TO_REQUEST);
                std::cin.get();
                std::cin.get();
                break;
            case 4: db.request_product();
                break;
            case 5: db.print_matrix( PRODUCT_TO_CREATE );
                std::cin.get();
                std::cin.get();
                break;
            case 6: db.order_material();
                break;
            case 7: db.print_matrix(MATERIAL_SHIPPING);
                std::cin.get();
                std::cin.get();
                break;
            case 8: db.arrived_material();
                break;
            case 9: db.print_matrix( MATERIAL_IN_STOCK );
                std::cin.get();
                std::cin.get();
                break;
            case 10: db.print_matrixPossibleProducts();
                break;
            case 11: db.order_product();
                break;
            case 12: db.print_matrix( PRODUCT_CREATING );
                std::cin.get();
                std::cin.get();
                break;
            case 13: db.arrived_product();
                break;
            case 14: db.print_matrix( PRODUCT_IN_STOCK );
                std::cin.get();
                std::cin.get();
                break;
            case 15: db.send_product();
                break;
            case 16: db.print_matrix( PRODUCT_SENT );
                std::cin.get();
                std::cin.get();
                break;
            case 17: print_flow();
                break;
            default:
                std::cout << ERROR("SELECT A VALID OPTION\n\n");
                break;
        }
        
    } while (val != 0);
    
    db.save_database();
    
    return 0;
}
