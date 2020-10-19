/* *************************************************************************************** //
 //                                                                                        //
 //  database.cpp                                                                          //
 //  neistpointTerminal                                                                    //
 //                                                                                        //
 //  Created by Didier Rodrigues Lopes on 2019.                                            //
 //  Copyright © 2019 Didier Lopes. All rights reserved.                                   //
 //                                                                                        //
 // *************************************************************************************** */

#include "database.h"

// Define possible sizes
std::string SIZES[NUM_SIZES] = {"XS",
                                "S",
                                "M",
                                "L",
                                "XL",
                                "XXL"};

// Define list of materials
std::string MATERIALS[NUM_MATERIALS] = {"White Shirt",
                                        "Grey Shirt",
                                        "Navy Shirt",
                                        "Black Shirt",
                                        "Yellow Sweater",
                                        "Grey Sweater",
                                        "Navy Sweater",
                                        "Black Sweater"};

// Define materialID associated with a certain productID.
// E.g. In order to produce "The Vintage White (Black) Shirt"
// a "White Shirt" is needed.
int MAT2PRO[NUM_PRODUCTS] = {0, 0, 0, 1, 2, 2, 3, 4, 5, 5, 6, 7};

// Define list of products
std::string PRODUCTS[NUM_PRODUCTS] = {  "The Vintage White (Black) Shirt",
                                        "The Vintage White (Red-black) Shirt",
                                        "The Plain White (Black) Shirt",
                                        "The Classic Grey (Black) Shirt",
                                        "The Original Navy (Yellow) Shirt",
                                        "The Vintage Navy (White-yellow) Shirt",
                                        "The Vintage Black (White) Shirt",
                                        "The Original Yellow (Black-White) Sweater",
                                        "The Original Grey (Black) Sweater",
                                        "The Vintage Grey (Black) Sweater",
                                        "The Original B. Navy (White) Sweater",
                                        "The Vintage B. Black (White-pink) Sweater"};


/**
 * Print available sizes, materials or products based on listID
 *
 * @param listID from listStrings
 */
void print_list(int listID)
{
    int ELEMS_LIST;
    std::string *pList;
    
    if (listID == LIST_SIZES)
    {
        ELEMS_LIST = NUM_SIZES;
        pList = &SIZES[0];
    }
    else if (listID == LIST_MATERIALS)
    {
        ELEMS_LIST = NUM_MATERIALS;
        pList = &MATERIALS[0];
    }
    else // listID == LIST_PRODUCTS
    {
        ELEMS_LIST = NUM_PRODUCTS;
        pList = &PRODUCTS[0];
    }
    
    // Print selected list accordingly
    for (int i = 0; i < ELEMS_LIST; i++)
    {
        std::cout << i+1 << " - " << pList[i] << "\n";
    }
}


/**
 * Return the number of items in a specified matrix
 *
 * @param matID from matrixDB
 * @return number of items in a particular matrix
 */
int Database::num_items(int matID)
{
    int *pMatrix = NULL;
    int counter = 0;

    switch(matID)
    {
        case MATERIAL_TO_REQUEST: pMatrix = &this->materialToRequest[0][0];
            break;
        case MATERIAL_SHIPPING: pMatrix = &this->materialShipping[0][0];
            break;
        case MATERIAL_IN_STOCK: pMatrix = &this->materialInStock[0][0];
            break;
        case PRODUCT_TO_CREATE: pMatrix = &this->productToCreate[0][0];
            break;
        case PRODUCT_CREATING: pMatrix = &this->productCreating[0][0];
            break;
        case PRODUCT_IN_STOCK: pMatrix = &this->productInStock[0][0];
            break;
        case PRODUCT_SENT: pMatrix = &this->productSent[0][0];
            break;
        default:
            break;
    }
    
    // This will iterate either through a matrix of materials, or stocks
    //so we need to select the iteration of rows accordingly. On the other
    //hand the iteration of columns remains constant, since this is the size
    int MAX_ELEM = (matID <= MATERIAL_IN_STOCK) ? NUM_MATERIALS : NUM_PRODUCTS;
    for (int elem = 0; elem < MAX_ELEM; elem++)
    {
        for (int size = 0; size < NUM_SIZES; size++)
        {
            counter += *(pMatrix + elem*NUM_SIZES + size);
        }
    }
    return counter;
}


// Load database from file: "../NeistPoint_database.csv"
void Database::load_database()
{
    std::ifstream file("../NeistPoint_database.csv");
    std::string line;
    // Pointer to first element of matrix matID
    int *pMatrix;
    
    for (int matID = (int) MATERIAL_TO_REQUEST ; matID <= (int) PRODUCT_SENT ; matID++)
    {
        switch(matID)
        {
            case MATERIAL_TO_REQUEST: pMatrix = &this->materialToRequest[0][0];
                break;
            case MATERIAL_SHIPPING: pMatrix = &this->materialShipping[0][0];
                break;
            case MATERIAL_IN_STOCK: pMatrix = &this->materialInStock[0][0];
                break;
            case PRODUCT_TO_CREATE: pMatrix = &this->productToCreate[0][0];
                break;
            case PRODUCT_CREATING: pMatrix = &this->productCreating[0][0];
                break;
            case PRODUCT_IN_STOCK: pMatrix = &this->productInStock[0][0];
                break;
            case PRODUCT_SENT: pMatrix = &this->productSent[0][0];
                break;
            default:
                return;
                break;
        }
        
        int MAX_ELEM = (matID <= MATERIAL_IN_STOCK) ? NUM_MATERIALS : NUM_PRODUCTS;
        for (int elem = 0; elem <= MAX_ELEM; elem++)
        {
            // This was a pain in the ass because file was saved as CRLF instead of LF
            std::getline(file, line, '\n');
            std::istringstream buffer(line);
            
            for (int size = 0; size <= NUM_SIZES; size++)
            {
                std::string val;
                std::getline(buffer, val, ';');
                
                if (elem == 0 || size == 0)
                {
                    // Jump name and size
                    continue;
                }
                
                std::stringstream field(val);
                field >> *(pMatrix + (elem-1)*NUM_SIZES + (size-1));
                //field >> pMatrix[elem-1][size-1];
            }
            
            if (elem == NUM_MATERIALS)
            {
                // burn line
                std::getline(file, line, '\n');
            }
        }
    }
    
    file.close();
}


// Save database in file: "../NeistPoint_database.csv"
void Database::save_database()
{
    std::ofstream file("../NeistPoint_database.csv");
    
    if (!file.is_open())
    {
        std::cout << ERROR("Unable to open file");
        return;
    }
    
    // Pointer to first element of matrix matID
    int *pMatrix;
    
    for (int matID = (int) MATERIAL_TO_REQUEST ; matID <= (int) PRODUCT_SENT ; matID++)
    {
        switch(matID)
        {
            case MATERIAL_TO_REQUEST:
                    file << "MATERIAL TO REQUEST;XS;S;M;L;XL;XXL;\n";
                    pMatrix = &this->materialToRequest[0][0];
                break;
            case MATERIAL_SHIPPING:
                    file << "MATERIAL SHIPPING;XS;S;M;L;XL;XXL;\n";
                    pMatrix = &this->materialShipping[0][0];
                break;
            case MATERIAL_IN_STOCK:
                    file << "MATERIAL IN STOCK;XS;S;M;L;XL;XXL;\n";
                    pMatrix = &this->materialInStock[0][0];
                break;
            case PRODUCT_TO_CREATE:
                    file << "PRODUCT TO CREATE;XS;S;M;L;XL;XXL;\n";
                    pMatrix = &this->productToCreate[0][0];
                break;
            case PRODUCT_CREATING:
                    file << "PRODUCT CREATING;XS;S;M;L;XL;XXL;\n";
                    pMatrix = &this->productCreating[0][0];
                break;
            case PRODUCT_IN_STOCK:
                    file << "PRODUCT IN STOCK;XS;S;M;L;XL;XXL;\n";
                    pMatrix = &this->productInStock[0][0];
                break;
            case PRODUCT_SENT:
                    file << "PRODUCT SENT;XS;S;M;L;XL;XXL;\n";
                    pMatrix = &this->productSent[0][0];
                break;
            default:
                return;
                break;
        }
        
        int MAX_ELEM = (matID <= MATERIAL_IN_STOCK) ? NUM_MATERIALS : NUM_PRODUCTS;
        for (int elem = 0; elem < MAX_ELEM; elem++)
        {
            file << ((matID <= MATERIAL_IN_STOCK) ? MATERIALS[elem] : PRODUCTS[elem]) << ";";
            for (int size = 0; size < NUM_SIZES; size++)
            {
                file << *(pMatrix + elem*NUM_SIZES + size) << ";";
            }
            file << "\n";
        }
        file << "\n";
    }
    
    file.close();
}


// Performs a request of product by a customer
void Database::request_productCustomer()
{
    std::cout << "What product does the customer wants?\n";
    std::cout << "(Option '0' will take you back to the menu)\n";
    
    int proChosen;
    int sizeChosen;
    
    while (1)
    {
        print_list( LIST_PRODUCTS );
        std::cout << "PRODUCT: ";
        std::cin >> proChosen;
        proChosen--;
        
        if (proChosen == -1)
        {
            return;
        }
        if (proChosen < 0 || proChosen > NUM_PRODUCTS-1)
        {
            std::cout << ERROR("SELECT A VALID PRODUCT\n\n");
            continue;
        }
        
        print_list( LIST_SIZES );
        std::cout << "SIZE: ";
        std::cin >> sizeChosen;
        sizeChosen--;
        
        if (proChosen == -1)
        {
            return;
        }
        if (sizeChosen < 0 || sizeChosen > NUM_SIZES-1)
        {
            std::cout << ERROR("SELECT A VALID ID\n\n");
            continue;
        }
        
        if (this->productInStock[proChosen][sizeChosen] > 0)
        {
            char r;
            std::cout << "The product is in Stock. Do you want to ship it? (y-yes, n-no)\n";
            std::cin >> r;
            
            if (r == 'y')
            {
                this->productInStock[proChosen][sizeChosen]--;
                this->productSent[proChosen][sizeChosen]++;
                
                std::cout << SIZES[sizeChosen] << " " << PRODUCTS[proChosen] << " sent!\n\n";
                return;
            }
            if (r == 'n')
            {
                return;
            }
        }
        else
        {
            std::cout << "The product is not in stock. ";
            
            int mat2pro = MAT2PRO[proChosen];
            
            char r;
            if (this->materialInStock[mat2pro][sizeChosen] > 0)
            {
                std::cout << "But the material necessary to produce it is. Do you want to add it to productsToCreate? (y-yes, n-no)\n";
                
                do
                {
                    std::cin >> r;
                    
                    if (r == 'y')
                    {
                        this->productToCreate[proChosen][sizeChosen]++;
                        
                        std::cout << SIZES[sizeChosen] << " " << PRODUCTS[proChosen] << " was added to the products to create!\n\n";
                        return;
                    }
                    else if (r == 'n')
                    {
                        return;
                    }
                    else
                    {
                        std::cout << "Type 'y' for yes, or 'n' for no!\n";
                    }
                } while(r != 'y' && r != 'n');
            }
            else
            {
                std::cout << "Neither the material necessary to produce it. Do you want to request it? (y-yes, n-no)\n";
                
                do
                {
                    std::cin >> r;
                    
                    if (r == 'y')
                    {
                        materialToRequest[mat2pro][sizeChosen]++;
                        
                        std::cout << SIZES[sizeChosen] << " " << MATERIALS[mat2pro] << " was added to the material to request!\n\n";
                        
                        this->productToCreate[proChosen][sizeChosen]++;
                        std::cout << "Furthermore " << SIZES[sizeChosen] << " " << PRODUCTS[proChosen] << " was added to the products to create!\n\n";
                        
                        return;
                    }
                    else if (r == 'n')
                    {
                        return;
                    }
                    else
                    {
                        std::cout << "Type 'y' for yes, or 'n' for no!\n";
                    }
                } while(r != 'y' && r != 'n');
            }
        }
    }
}


// Performs a request of material (done by management)
//e.g. to have some stock
void Database::request_material()
{
    std::cout << BOLD(NORMAL("What material do you want to request?\n"));
    std::cout << "(Option '0' will take you back to the menu)\n";
    
    int matChosen;
    int sizeChosen;
    int quantChosen;
    
    while (true)
    {
        // Material selection
        print_list( LIST_MATERIALS );
        std::cout << BOLD(NORMAL("MATERIAL: "));
        std::cin >> matChosen;
        matChosen--;
        
        if (matChosen == -1)
        {
            return;
        }
        if (matChosen < 0 || matChosen > NUM_MATERIALS-1)
        {
            std::cout << ERROR("SELECT A VALID MATERIAL ID\n\n");
            continue;
        }
        
        // Size selection
        print_list( LIST_SIZES );
        std::cout << BOLD(NORMAL("SIZE: "));
        std::cin >> sizeChosen;
        sizeChosen--;
        
        if (sizeChosen == -1)
        {
            return;
        }
        if (sizeChosen < 0 || sizeChosen > NUM_SIZES-1)
        {
            std::cout << ERROR("SELECT A VALID SIZE ID\n\n");
            continue;
        }
        
        // Quantity selection
        std::cout << BOLD(NORMAL("QUANTITY: "));
        std::cin >> quantChosen;
        
        this->materialToRequest[matChosen][sizeChosen] += quantChosen;
        
        std::cout << SUCCESS("The following material has been added to the request list: ") << quantChosen << " " << SIZES[sizeChosen] << " " << MATERIALS[matChosen] << "\n\n";
        return;
    }
}


// Performs a request of product (done by management)
//e.g. to have a new sweater from something was in stock
void Database::request_product()
{
    std::cout << BOLD(NORMAL("What product do you want to request?\n"));
    std::cout << "(Option '0' will take you back to the menu)\n";
    
    int proChosen;
    int sizeChosen;
    int quantChosen;
    
    while (true)
    {
        print_list( LIST_PRODUCTS );
        std::cout << "PRODUCT: ";
        std::cin >> proChosen;
        proChosen--;
        
        if (proChosen == -1)
        {
            return;
        }
        if (proChosen < 0 || proChosen > NUM_PRODUCTS-1)
        {
            std::cout << ERROR("SELECT A VALID PRODUCT\n\n");
            continue;
        }
        
        print_list( LIST_SIZES );
        std::cout << "SIZE: ";
        std::cin >> sizeChosen;
        sizeChosen--;
        
        if (proChosen == -1)
        {
            return;
        }
        if (sizeChosen < 0 || sizeChosen > NUM_SIZES-1)
        {
            std::cout << ERROR("SELECT A VALID ID\n\n");
            continue;
        }
        
        // Quantity selection
        std::cout << BOLD(NORMAL("QUANTITY: "));
        std::cin >> quantChosen;

        this->productToCreate[proChosen][sizeChosen] += quantChosen;
        
        std::cout << SUCCESS("The following product has been added to the request list: ") << quantChosen << " " << SIZES[sizeChosen] << " " << PRODUCTS[proChosen] << "\n\n";
        return;
    }
}


// Based on the materialToRequest matrix orders material
//which will end up being passed to materialShipping matrix
void Database::order_material()
{
    int c = 2;
    do
    {
        std::cout << BOLD(NORMAL("What material was ordered?\n"));
        std::cout << "(Option '0' will take you back to the menu)\n";
        
        if (this->num_items(MATERIAL_TO_REQUEST))
        {
            std::cout << "1 - All requested material\n";
            std::cout << "2 - Only some material\n";
            std::cin >> c;
            
            if (c == 0)
            {
                return;
            }
        }
  
        if (c == 1)
        {
            std::cout << WARNING("The following material will be ordered\n");
            this->print_matrix( MATERIAL_TO_REQUEST );
            
            char r;
            do
            {
                std::cout << WARNING("Do you confirm? (y-yes, n-no)\n");
                std::cin >> r;
                
                if (r == 'y')
                {
                    for (int material = 0; material < NUM_MATERIALS; material++)
                    {
                        for (int size = 0; size < NUM_SIZES; size++)
                        {
                            this->materialShipping[material][size] += this->materialToRequest[material][size];
                            this->materialToRequest[material][size] = 0;
                        }
                    }
                    std::cout << SUCCESS("All requested material has been ordered!\n\n");
                    return;
                }
                else if (r == 'n')
                {
                    return;
                }
                else
                {
                    std::cout << ERROR("Type 'y' for yes, or 'n' for no!\n");
                }
            } while(r != 'y' && r != 'n');
        }
        else if (c == 2)
        {
            std::cout << BOLD(NORMAL("Select some material:\n"));
            
            int matChosen;
            int sizeChosen;
            int quantChosen;
            
            while (true)
            {
                // Material selection
                print_list( LIST_MATERIALS );
                std::cout << BOLD(NORMAL("MATERIAL: "));
                std::cin >> matChosen;
                matChosen--;
                
                if (matChosen == -1)
                {
                    return;
                }
                if (matChosen < 0 || matChosen > NUM_MATERIALS-1)
                {
                    std::cout << ERROR("SELECT A VALID MATERIAL ID\n\n");
                    continue;
                }
                
                // Size selection
                print_list( LIST_SIZES );
                std::cout << BOLD(NORMAL("SIZE: "));
                std::cin >> sizeChosen;
                sizeChosen--;
                
                if (sizeChosen == -1)
                {
                    return;
                }
                if (sizeChosen < 0 || sizeChosen > NUM_SIZES-1)
                {
                    std::cout << ERROR("SELECT A VALID SIZE ID\n\n");
                    continue;
                }
                
                // Quantity selection
                std::cout << BOLD(NORMAL("QUANTITY: "));
                std::cin >> quantChosen;
                
                if (quantChosen > this->materialToRequest[matChosen][sizeChosen])
                {
                    int extraQuant = quantChosen-this->materialToRequest[matChosen][sizeChosen];
                    std::cout  << WARNING("WARNING: ") << "An extra " << extraQuant << " " << MATERIALS[matChosen] << " " << SIZES[sizeChosen] << " from material to be requested will be ordered!\n";
                    
                    char r;
                    do
                    {
                        std::cout << WARNING("Is this expected? (y-yes, n-no)\n");
                        std::cin >> r;
                        
                        if (r == 'y')
                        {
                            continue;
                        }
                        else if (r == 'n')
                        {
                            return;
                        }
                        else
                        {
                            std::cout << ERROR("Type 'y' for yes, or 'n' for no!\n");
                        }
                    } while(r != 'y' && r != 'n');
                }
                
                this->materialToRequest[matChosen][sizeChosen] -= quantChosen;
                this->materialToRequest[matChosen][sizeChosen] = std::max(this->materialToRequest[matChosen][sizeChosen], 0);

                this->materialShipping[matChosen][sizeChosen] += quantChosen;
                
                std::cout << SUCCESS("The following material has been ordered: ") << quantChosen << " " << SIZES[sizeChosen] << " " << MATERIALS[matChosen] << "\n\n";
                return;
            }
        }
        else
        {
            std::cout << ERROR("SELECT A VALID OPTION\n");
        }
    } while (c < 0 || c > 2);
}


// Based on the materialShipping matrix deems material as arrived
//which will end up being passed to materialInStock matrix
void Database::arrived_material()
{
    int c = 2;
    do
    {
        std::cout << BOLD(NORMAL("What material has arrived?\n"));
        std::cout << "(Option '0' will take you back to the menu)\n";
        
        if (this->num_items(MATERIAL_SHIPPING))
        {
            std::cout << "1 - All shipping material\n";
            std::cout << "2 - Only some material\n";
            std::cin >> c;
            
            if (c == 0)
            {
                return;
            }
        }
        
        if (c == 1)
        {
            std::cout << WARNING("The following material will be marked as arrived\n");
            this->print_matrix( MATERIAL_SHIPPING );
            
            char r;
            do
            {
                std::cout << WARNING("Do you confirm? (y-yes, n-no)\n");
                std::cin >> r;
                
                if (r == 'y')
                {
                    for (int material = 0; material < NUM_MATERIALS; material++)
                    {
                        for (int size = 0; size < NUM_SIZES; size++)
                        {
                            this->materialInStock[material][size] += this->materialShipping[material][size];
                            this->materialShipping[material][size] = 0;
                        }
                    }
                    std::cout << SUCCESS("All materials shipping have arrived!\n\n");
                    return;
                }
                else if (r == 'n')
                {
                    return;
                }
                else
                {
                    std::cout << ERROR("Type 'y' for yes, or 'n' for no!\n");
                }
            } while(r != 'y' && r != 'n');
        }
        else if (c == 2)
        {
            std::cout << BOLD(NORMAL("Select some material:\n"));
            
            int matChosen;
            int sizeChosen;
            int quantChosen;
            
            while (true)
            {
                // Material selection
                print_list( LIST_MATERIALS );
                std::cout << BOLD(NORMAL("MATERIAL: "));
                std::cin >> matChosen;
                matChosen--;
                
                if (matChosen == -1)
                {
                    return;
                }
                if (matChosen < 0 || matChosen > NUM_MATERIALS-1)
                {
                    std::cout << ERROR("SELECT A VALID MATERIAL ID\n\n");
                    continue;
                }
                
                // Size selection
                print_list( LIST_SIZES );
                std::cout << BOLD(NORMAL("SIZE: "));
                std::cin >> sizeChosen;
                sizeChosen--;
                
                if (sizeChosen == -1)
                {
                    return;
                }
                if (sizeChosen < 0 || sizeChosen > NUM_SIZES-1)
                {
                    std::cout << ERROR("SELECT A VALID SIZE ID\n\n");
                    continue;
                }
                
                // Quantity selection
                std::cout << BOLD(NORMAL("QUANTITY: "));
                std::cin >> quantChosen;
                
                if (quantChosen > this->materialShipping[matChosen][sizeChosen])
                {
                    int extraQuant = quantChosen-this->materialShipping[matChosen][sizeChosen];
                    std::cout  << WARNING("WARNING: ") << "An extra " << extraQuant << " " << MATERIALS[matChosen] << " " << SIZES[sizeChosen] << " have arrived!\n\n";
                    
                    char r;
                    do
                    {
                        std::cout << WARNING("Is this expected? (y-yes, n-no)\n");
                        std::cin >> r;
                        
                        if (r == 'y')
                        {
                            continue;
                        }
                        else if (r == 'n')
                        {
                            return;
                        }
                        else
                        {
                            std::cout << ERROR("Type 'y' for yes, or 'n' for no!\n");
                        }
                    } while(r != 'y' && r != 'n');
                }
                
                this->materialShipping[matChosen][sizeChosen] -= quantChosen;
                this->materialShipping[matChosen][sizeChosen] = std::max(this->materialShipping[matChosen][sizeChosen], 0);
                
                this->materialInStock[matChosen][sizeChosen] += quantChosen;
                
                std::cout << SUCCESS("The following material has arrived: ") << quantChosen << " " << SIZES[sizeChosen] << " " << MATERIALS[matChosen] << "\n\n";
                return;
            }
        }
        else
        {
            std::cout << ERROR("SELECT A VALID OPTION\n");
        }
    } while (c < 0 || c > 2);
}


// Based on the productToCreate matrix order some products to be made
//this is equivalent to taking the necessary material to the producer
//hence removing the material from materialInStock matrix. This products
//on the making are hold on productCreating matrix.
// Sequence of events, when product is ordered:
//  - Add X products to the productCreating database
//  - Remove X materials from the materialInStock database
//  - Give a warning in case X is bigger than the amount of the material necessary to produce this product in materialInStock database
void Database::order_product()
{
    std::cout << BOLD(NORMAL("What product was ordered?\n"));
    std::cout << "(Option '0' will take you back to the menu)\n";
    
    if (this->num_items(MATERIAL_IN_STOCK) == 0)
    {
        std::cout << "There are no material in stock, therefore, no product can be created\n";
        return;
    }
    
    std::cout << BOLD(NORMAL("Select some product:\n"));

    int proChosen;
    int sizeChosen;
    int quantChosen;

    while (true)
    {
        // Material selection
        print_list(LIST_PRODUCTS);
        std::cout << BOLD(NORMAL("PRODUCT: "));
        std::cin >> proChosen;
        proChosen--;
        
        if (proChosen == -1)
        {
            return;
        }
        if (proChosen < 0 || proChosen > NUM_PRODUCTS-1)
        {
            std::cout << ERROR("SELECT A VALID PRODUCT ID\n\n");
            continue;
        }
        
        // Size selection
        print_list(LIST_SIZES);
        std::cout << "SIZE: ";
        std::cin >> sizeChosen;
        sizeChosen--;
        
        if (sizeChosen == -1)
        {
            return;
        }
        if (sizeChosen < 0 || sizeChosen > NUM_SIZES-1)
        {
            std::cout << ERROR("SELECT A VALID SIZE ID\n\n");
            continue;
        }
        
        // Quantity selection
        std::cout << BOLD(NORMAL("QUANTITY: "));
        std::cin >> quantChosen;
        
        int mat2pro = MAT2PRO[proChosen];
        if (quantChosen > this->materialInStock[mat2pro][sizeChosen])
        {
            std::cout << ERROR("There is not enough material stock to produce these products!\n\n");
            continue;
        }
        
        if (quantChosen > this->productToCreate[proChosen][sizeChosen])
        {
            int extraQuant = quantChosen-this->productToCreate[proChosen][sizeChosen];
            std::cout << WARNING("WARNING: ") << "An extra " << extraQuant << " " << PRODUCTS[proChosen] << " " << SIZES[sizeChosen] << " will be created compared to productsToCreate!\n";
            
            char r;
            do
            {
                std::cout << WARNING("Is this expected? (y-yes, n-no)\n");
                std::cin >> r;
                
                if (r == 'y')
                {
                    continue;
                }
                else if (r == 'n')
                {
                    return;
                }
                else
                {
                    std::cout << ERROR("Type 'y' for yes, or 'n' for no!\n");
                }
            } while(r != 'y' && r != 'n');
        }
        
        this->productToCreate[proChosen][sizeChosen] -= quantChosen;
        this->productToCreate[proChosen][sizeChosen] = std::max(this->productToCreate[proChosen][sizeChosen], 0);
        
        this->productCreating[proChosen][sizeChosen] += quantChosen;
        
        std::cout << SUCCESS("The following products have been ordered: ") << quantChosen << " " << SIZES[sizeChosen] << " " << PRODUCTS[proChosen] << "\n\n";
        return;
    }
}


// Based on the productCreating matrix some products must be selected
//as they have made it back to the headquarters company. At this point
//the products are added to the productInStock matrix.
// Sequence of events, when a product has arrived:
//  - Add X products to the productInStock database
//  - Remove X products from the productCreating database
//  - Give a warning in case X is bigger than the amount of this product in productCreating database
void Database::arrived_product()
{
    int c = 2;
    do
    {
        std::cout << BOLD(NORMAL("What product has arrived?\n"));
        std::cout << "(Option '0' will take you back to the menu)\n";
        
        if (this->num_items(PRODUCT_CREATING) > 0)
        {
            std::cout << "1 - All creating products\n";
            std::cout << "2 - Only some products\n";
            std::cin >> c;
            
            if (c == 0)
            {
                return;
            }
        }
        
        if (c == 1)
        {
            std::cout << WARNING("The following products will be marked as arrived\n");
            this->print_matrix(PRODUCT_CREATING);
            
            char r;
            do
            {
                std::cout << WARNING("Do you confirm? (y-yes, n-no)\n");
                std::cin >> r;
                
                if (r == 'y')
                {
                    for (int product = 0; product < NUM_PRODUCTS; product++)
                    {
                        for (int size = 0; size < NUM_SIZES; size++)
                        {
                            this->productInStock[product][size] += this->productCreating[product][size];
                            this->productCreating[product][size] = 0;
                        }
                    }
                    std::cout << SUCCESS("All products shipping have arrived!\n\n");
                    return;
                }
                else if (r == 'n')
                {
                    return;
                }
                else
                {
                    std::cout << ERROR("Type 'y' for yes, or 'n' for no!\n");
                }
            } while(r != 'y' && r != 'n');
        }
        else if (c == 2)
        {
            std::cout << BOLD(NORMAL("Select some product:\n"));
            
            int proChosen;
            int sizeChosen;
            int quantChosen;
            
            while (true)
            {
                // Material selection
                print_list(LIST_PRODUCTS);
                std::cout << BOLD(NORMAL("PRODUCT: "));
                std::cin >> proChosen;
                proChosen--;
                
                if (proChosen == -1)
                {
                    return;
                }
                if (proChosen < 0 || proChosen > NUM_PRODUCTS-1)
                {
                    std::cout << ERROR("SELECT A VALID PRODUCT ID\n\n");
                    continue;
                }
                
                // Size selection
                print_list(LIST_SIZES);
                std::cout << BOLD(NORMAL("SIZE: "));
                std::cin >> sizeChosen;
                sizeChosen--;
                
                if (sizeChosen == -1)
                {
                    return;
                }
                if (sizeChosen < 0 || sizeChosen > NUM_SIZES-1)
                {
                    std::cout << ERROR("SELECT A VALID SIZE ID\n\n");
                    continue;
                }
                
                // Quantity selection
                std::cout << BOLD(NORMAL("QUANTITY: "));
                std::cin >> quantChosen;
                
                if (quantChosen > this->productCreating[proChosen][sizeChosen])
                {
                    int extraQuant = quantChosen-this->productCreating[proChosen][sizeChosen];
                    std::cout << WARNING("WARNING: ") << "An extra " << extraQuant << " " << PRODUCTS[proChosen] << " " << SIZES[sizeChosen] << " not ordered product(s) have arrived!\n\n";
                    
                    char r;
                    do
                    {
                        std::cout << WARNING("Is this expected? (y-yes, n-no)\n");
                        std::cin >> r;
                        
                        if (r == 'y')
                        {
                            continue;
                        }
                        else if (r == 'n')
                        {
                            return;
                        }
                    } while(r != 'y' && r != 'n');
                }
                
                this->productCreating[proChosen][sizeChosen] -= quantChosen;
                this->productCreating[proChosen][sizeChosen] = std::max(this->productCreating[proChosen][sizeChosen], 0);
                
                this->productInStock[proChosen][sizeChosen] += quantChosen;
                
                std::cout << SUCCESS("The following products have arrived: ") << quantChosen << " " << SIZES[sizeChosen] << " " << PRODUCTS[proChosen] << "\n\n";
                return;
            }
        }
        else
        {
            std::cout << ERROR("SELECT A VALID OPTION\n");
        }
    } while (c < 0 || c > 2);
}


// Based on the productInStock matrix we are now able to send some products
//to the customers. Hence, these products are now added to productSent matrix,
//which can later be used for analysis of each product performance.
// Sequence of events, when a product must be sent to a customer.
//  - Add X products to the productSent database
//  - Remove X products from the productInStock database
//  - Give a warning in case X is bigger than the amount of this product in productsInStock database
void Database::send_product()
{
    int c = 2;
    do
    {
        std::cout << BOLD(NORMAL("What product was sent?\n"));
        std::cout << "(Option '0' will take you back to the menu)\n";
        
        if (this->num_items(PRODUCT_IN_STOCK) > 0)
        {
            std::cout << "1 - All products in stock\n";
            std::cout << "2 - Only some products\n";
            std::cin >> c;
            
            if (c == 0)
            {
                return;
            }
        }
        
        if (c == 1)
        {
            std::cout << WARNING("The following products will be sent\n");
            this->print_matrix(PRODUCT_IN_STOCK);
            
            char r;
            do
            {
                std::cout << WARNING("Do you confirm? (y-yes, n-no)\n");
                std::cin >> r;
                
                if (r == 'y')
                {
                    for (int product = 0; product < NUM_PRODUCTS; product++)
                    {
                        for (int size = 0; size < NUM_SIZES; size++)
                        {
                            this->productSent[product][size] += this->productInStock[product][size];
                            this->productInStock[product][size] = 0;
                        }
                    }
                    std::cout << SUCCESS("All products in stock have been sent!\n\n");
                    return;
                }
                else if (r == 'n')
                {
                    return;
                }
                else
                {
                    std::cout << ERROR("Type 'y' for yes, or 'n' for no!\n");
                }
            } while(r != 'y' && r != 'n');
        }
        else if (c == 2)
        {
            std::cout << BOLD(NORMAL("Select some product:\n"));
            
            int proChosen;
            int sizeChosen;
            int quantChosen;
            
            while (true)
            {
                // Material selection
                print_list(LIST_PRODUCTS);
                std::cout << BOLD(NORMAL("PRODUCT: "));
                std::cin >> proChosen;
                proChosen--;
                
                if (proChosen == -1)
                {
                    return;
                }
                if (proChosen < 0 || proChosen > NUM_PRODUCTS-1)
                {
                    std::cout << ERROR("SELECT A VALID PRODUCT ID\n\n");
                    continue;
                }
                
                // Size selection
                print_list(LIST_SIZES);
                std::cout << BOLD(NORMAL("SIZE: "));
                std::cin >> sizeChosen;
                sizeChosen--;
                
                if (sizeChosen == -1)
                {
                    return;
                }
                if (sizeChosen < 0 || sizeChosen > NUM_SIZES-1)
                {
                    std::cout << ERROR("SELECT A VALID SIZE ID\n\n");
                    continue;
                }
                
                // Quantity selection
                std::cout << BOLD(NORMAL("QUANTITY: "));
                std::cin >> quantChosen;
                
                if (quantChosen > this->productInStock[proChosen][sizeChosen])
                {
                    int extraQuant = quantChosen-this->productInStock[proChosen][sizeChosen];
                    std::cout << WARNING("WARNING: ") << "An extra " << extraQuant << " " << PRODUCTS[proChosen] << " " << SIZES[sizeChosen] << " will be sent!\n";
                    
                    char r;
                    do
                    {
                        std::cout << "Is this expected? (y-yes, n-no)\n";
                        std::cin >> r;
                        
                        if (r == 'y')
                        {
                            continue;
                        }
                        else if (r == 'n')
                        {
                            return;
                        }
                        else
                        {
                            std::cout << ERROR("Type 'y' for yes, or 'n' for no!\n");
                        }
                    } while(r != 'y' && r != 'n');
                }
                
                this->productInStock[proChosen][sizeChosen] -= quantChosen;
                this->productInStock[proChosen][sizeChosen] = std::max(this->productInStock[proChosen][sizeChosen], 0);
                
                this->productSent[proChosen][sizeChosen] += quantChosen;
                
                std::cout << SUCCESS("The following products have been send: ") << quantChosen << " " << SIZES[sizeChosen] << " " << PRODUCTS[proChosen] << "\n\n";
                return;
            }
        }
        else
        {
            std::cout << ERROR("SELECT A VALID OPTION\n");
        }
    } while (c < 0 || c > 2);
}


/**
 * Prints one of the database matrices specified by "matrixDB"
 *
 * @param matID from matrixDB
 */
void Database::print_matrix(int matID)
{
    // Pointer to first element of matrix matID
    int *pMatrix;
    
    switch(matID)
    {
        case MATERIAL_TO_REQUEST:
            std::cout << "MATERIAL TO REQUEST  |  XS |  S  |  M  |  L  |  XL | XXL \n";
            pMatrix = &this->materialToRequest[0][0];
            break;
        case MATERIAL_SHIPPING:
            std::cout << "MATERIAL SHIPPING    |  XS |  S  |  M  |  L  |  XL | XXL \n";
            pMatrix = &this->materialShipping[0][0];
            break;
        case MATERIAL_IN_STOCK:
            std::cout << "MATERIAL IN STOCK    |  XS |  S  |  M  |  L  |  XL | XXL \n";
            pMatrix = &this->materialInStock[0][0];
            break;
        case PRODUCT_TO_CREATE:
            std::cout << "PRODUCT TO CREATE                         |  XS |  S  |  M  |  L  |  XL | XXL \n";
            pMatrix = &this->productToCreate[0][0];
            break;
        case PRODUCT_CREATING:
            std::cout << "PRODUCT CREATING                          |  XS |  S  |  M  |  L  |  XL | XXL \n";
            pMatrix = &this->productCreating[0][0];
            break;
        case PRODUCT_IN_STOCK:
            std::cout << "PRODUCT IN STOCK                          |  XS |  S  |  M  |  L  |  XL | XXL \n";
            pMatrix = &this->productInStock[0][0];
            break;
        case PRODUCT_SENT:
            std::cout << "PRODUCT SENT                              |  XS |  S  |  M  |  L  |  XL | XXL \n";
            pMatrix = &this->productSent[0][0];
            break;
        default:
            return;
            break;
    }
    
    int MAX_ELEM = (matID <= MATERIAL_IN_STOCK) ? NUM_MATERIALS : NUM_PRODUCTS;
    for (int elem = 0; elem < MAX_ELEM; elem++)
    {
        if (matID <= MATERIAL_IN_STOCK)
        {
            std::cout << "---------------------------------------------------------\n";
            std::cout <<MATERIALS[elem];
            for (int i = (int) MATERIALS[elem].length(); i<=20 ; i++)
            {
                std::cout << " ";
            }
        }
        else // matID >= PRODUCT_TO_CREATE
        {
            std::cout << "------------------------------------------------------------------------------\n";
            std::cout << PRODUCTS[elem];
            for (int i = (int) PRODUCTS[elem].length(); i<=41 ; i++)
            {
                std::cout << " ";
            }
        }
        
        for (int size = 0; size < NUM_SIZES; size++)
        {
            int val = *(pMatrix + elem*NUM_SIZES + size);
            
            if (val == 0)
            {
                std::cout << "|     ";
            }
            else if (val < 9)
            {
                std::cout << "|  " << val << "  ";
            }
            else if (val < 99)
            {
                std::cout << "|  " << val << " ";
            }
            else
            {
                std::cout << "| " << val << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


// Print matrix of possible products to create
//based on available material in stock
void Database::print_matrixPossibleProducts()
{
    std::cout << "POSSIBLE PRODUCTS TO CREATE               |  XS |  S  |  M  |  L  |  XL | XXL \n";
    
    for (int pro = 0; pro < NUM_PRODUCTS; pro++)
    {
        std::cout << "------------------------------------------------------------------------------\n";
        std::cout << PRODUCTS[pro];
        for (int i = (int) PRODUCTS[pro].length(); i<=41 ; i++)
        {
            std::cout << " ";
        }
        
        int mat2pro = MAT2PRO[pro];
        
        for (int size = 0; size < NUM_SIZES; size++)
        {
            int val = 0;
            int material = this->materialInStock[mat2pro][size];
            int product = this->productToCreate[pro][size];
            
            while (material > 0 && product > 0)
            {
                val++;
                material--;
                product--;
            }
            if (val == 0)
            {
                std::cout << "|     ";
            }
            else if (val < 9)
            {
                std::cout << "|  " << val << "  ";
            }
            else if (val < 99)
            {
                std::cout << "|  " << val << " ";
            }
            else
            {
                std::cout << "| " << val << " ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
