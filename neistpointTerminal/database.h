/* *************************************************************************************** //
 //                                                                                        //
 //  database.h                                                                            //
 //  neistpointTerminal                                                                    //
 //                                                                                        //
 //  Created by Didier Rodrigues Lopes on 2019.                                            //
 //  Copyright © 2019 Didier Lopes. All rights reserved.                                   //
 //                                                                                        //
 // *************************************************************************************** */

#ifndef database_h
#define database_h

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define RESET  "\x1B[0m"

#define RED    "\x1B[31m"
#define GREEN  "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE   "\x1B[34m"
#define CYAN   "\x1B[36m"
#define WHITE  "\x1B[37m"

#define BOLD(x) "\x1B[1m" x RESET

#define ERROR(x)   RED x RESET
#define SUCCESS(x) GREEN x RESET
#define WARNING(x) YELLOW x RESET
#define INFO(x)    BLUE x RESET
#define ACTION(x)  CYAN x RESET
#define NORMAL(x)  WHITE x RESET

// Define some variables
#define NUM_SIZES      6
#define NUM_MATERIALS  8
#define NUM_PRODUCTS   12

// Define ID associated with each list of sizes, materials and products
enum listStrings {
    LIST_SIZES,
    LIST_MATERIALS,
    LIST_PRODUCTS
};

// Define ID associated with each database
enum matrixDB {
    MATERIAL_TO_REQUEST = 0,
    MATERIAL_SHIPPING   = 1,
    MATERIAL_IN_STOCK   = 2,
    PRODUCT_TO_CREATE   = 3,
    PRODUCT_CREATING    = 4,
    PRODUCT_IN_STOCK    = 5,
    PRODUCT_SENT        = 6
};

class Database
{
private:
    int materialToRequest[NUM_MATERIALS][NUM_SIZES] = {0};
    int materialShipping[NUM_MATERIALS][NUM_SIZES] = {0};
    int materialInStock[NUM_MATERIALS][NUM_SIZES] = {0};
    int productToCreate[NUM_PRODUCTS][NUM_SIZES] = {0};
    int productCreating[NUM_PRODUCTS][NUM_SIZES] = {0};
    int productInStock[NUM_PRODUCTS][NUM_SIZES] = {0};
    int productSent[NUM_PRODUCTS][NUM_SIZES] = {0};
    
public:
    void load_database();
    void save_database();
    
    void request_productCustomer();
    
    void request_material();
    void request_product();
    
    void order_material();
    void arrived_material();
    
    void order_product();
    void arrived_product();
    
    void send_product();
    
    int num_items(int matID);
    void print_matrix(int matID);
    
    void print_matrixPossibleProducts();
};

#endif /* database_h */
