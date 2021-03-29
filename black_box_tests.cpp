//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Martin Zmitko <xzmitk01@stud.fit.vutbr.cz>
// $Date:       $2021-2-22
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Martin Zmitko
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

/*** Konec souboru black_box_tests.cpp ***/

class EmptyTree : public ::testing::Test
{
protected:
    BinaryTree tree;
};

class NonEmptyTree : public ::testing::Test
{
protected:
    virtual void SetUp(){
        tree = BinaryTree();
        for(int i = 0; i < 10; i += 2){
            tree.InsertNode(i);
        }
    }
    BinaryTree tree;
};

class TreeAxioms : public ::testing::Test
{
protected:
    virtual void SetUp(){
        tree = BinaryTree();
        for(int i = 0; i < 10; i++){
            tree.InsertNode(i);
        }
    }
    BinaryTree tree;
};

TEST_F(EmptyTree, InsertNode)
{
    std::pair<bool, BinaryTree::Node_t*> result = tree.InsertNode(1);
    EXPECT_TRUE(result.first);
    std::pair<bool, BinaryTree::Node_t*> result2 = tree.InsertNode(1);
    EXPECT_FALSE(result2.first);
    EXPECT_EQ(result.second, result2.second);
    for(int i = 2; i < 6; i++){
        EXPECT_TRUE(tree.InsertNode(i).first);
    }
}

TEST_F(EmptyTree, DeleteNode)
{
    EXPECT_FALSE(tree.DeleteNode(1));
    tree.InsertNode(1);
    tree.InsertNode(3);
    EXPECT_TRUE(tree.DeleteNode(1));
    std::vector<BinaryTree::Node_t *> outAllNodes;
    tree.GetAllNodes(outAllNodes);
    EXPECT_EQ(outAllNodes[0]->key, 3);
}

TEST_F(EmptyTree, FindNode)
{
    tree.InsertNode(1);
    tree.InsertNode(3);
    EXPECT_EQ(tree.FindNode(3)->key, 3);
    EXPECT_EQ(tree.FindNode(2), (Node_t*)NULL);
}

TEST_F(NonEmptyTree, InsertNode)
{
    EXPECT_FALSE(tree.InsertNode(0).first);
    EXPECT_TRUE(tree.InsertNode(1).first);
}

TEST_F(NonEmptyTree, DeleteNode)
{
    EXPECT_TRUE(tree.DeleteNode(2));
    EXPECT_FALSE(tree.DeleteNode(3));
}

TEST_F(NonEmptyTree, FindNode)
{
    EXPECT_EQ(tree.FindNode(0)->key, 0);
    EXPECT_EQ(tree.FindNode(1), (Node_t*)NULL);
    tree.InsertNode(1);
    EXPECT_NE(tree.FindNode(1), (Node_t*)NULL);
}

TEST_F(TreeAxioms, Axiom1)
{
    std::vector<BinaryTree::Node_t *> outLeafNodes;
    tree.GetLeafNodes(outLeafNodes);
    for(int i = 0; i < outLeafNodes.size(); i++){
        EXPECT_EQ(outLeafNodes[i]->color, BLACK);
    }
}

TEST_F(TreeAxioms, Axiom2)
{
    std::vector<BinaryTree::Node_t *> allNodes;
    tree.GetNonLeafNodes(allNodes);
    for(int i = 0; i < allNodes.size(); i++){
        if(allNodes[i]->color == BLACK) continue;
        EXPECT_EQ(allNodes[i]->pLeft->color, BLACK);
        EXPECT_EQ(allNodes[i]->pRight->color, BLACK);
    }
}

TEST_F(TreeAxioms, Axiom3)
{
    std::vector<BinaryTree::Node_t *> leafNodes;
    tree.GetLeafNodes(leafNodes);
    if(leafNodes.size() > 0){
        Node_t *root = tree.GetRoot();
        int pathLen = 0;
        Node_t *node = leafNodes[0];
        while((node = node->pParent) != root) 
            if(node->color == BLACK) 
                pathLen++;

        for(int i = 0; i < leafNodes.size(); i++){
            Node_t *node = leafNodes[i];
            int len = 0;
            while((node = node->pParent) != root) 
                if(node->color == BLACK) 
                    len++;
            EXPECT_EQ(pathLen, len);
        }
    }
}