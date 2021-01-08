#include <iostream>
#include <vector>
#include <unordered_map>
#include <codecvt>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include <locale>

using namespace std;

struct node
{
    string name;
    unordered_map<wstring, shared_ptr<node>> edges;

    node(string str) : name(str) {}
};

class Solution
{
public:
    Solution()
    {
        buildNodes();
        buildEdges();
    }

    void buildNodes()
    {
        root = make_shared<node>("自己");
        MB = make_shared<node>("自己");
        MG = make_shared<node>("自己");
        father = make_shared<node>("父親");
        mother = make_shared<node>("母親");
        wife = make_shared<node>("妻");
        husband = make_shared<node>("夫");

        OlderBrother = make_shared<node>("哥哥");
        YoungerBrother = make_shared<node>("弟弟");
        OlderSister = make_shared<node>("姊姊");
        YoungerSister = make_shared<node>("妹妹");

        B_Son = make_shared<node>("兒子");
        B_Daughter = make_shared<node>("女兒");
        G_Son = make_shared<node>("兒子");
        G_Daughter = make_shared<node>("女兒");
        B_DIL = make_shared<node>("媳婦");
        B_SIL = make_shared<node>("女婿");
        G_DIL = make_shared<node>("媳婦");
        G_SIL = make_shared<node>("女婿");
        B_Grandson = make_shared<node>("孫子");
        B_GrandDau = make_shared<node>("孫女");
        G_Grandson = make_shared<node>("孫子");
        G_GrandDau = make_shared<node>("孫女");
        B_Dau_Grandson = make_shared<node>("外孫");
        G_Dau_Grandson = make_shared<node>("外孫");

        O_SIL = make_shared<node>("嫂嫂");
        Y_SIL = make_shared<node>("弟媳");
        O_BIL = make_shared<node>("姊夫");
        Y_BIL = make_shared<node>("妹夫");
        O_B_Nephew = make_shared<node>("姪子");
        O_B_Concubine = make_shared<node>("姪女");
        Y_B_Nephew = make_shared<node>("姪子");
        Y_B_Concubine = make_shared<node>("姪女");
        O_Sis_Nephew = make_shared<node>("外甥");
        O_Sis_Concubine = make_shared<node>("外甥女");
        Y_Sis_Nephew = make_shared<node>("外甥");
        Y_Sis_Concubine = make_shared<node>("外甥女");

        F_B_Uncle = make_shared<node>("伯父");
        F_B_Y_Uncle = make_shared<node>("叔父");
        F_B_O_Aunt = make_shared<node>("伯母");
        F_B_Y_Aunt = make_shared<node>("嬸嬸");
        F_O_B_O_B_Cousin = make_shared<node>("堂兄");
        F_O_B_Y_B_Cousin = make_shared<node>("堂弟");
        F_O_B_O_G_Cousin = make_shared<node>("堂姊");
        F_O_B_Y_G_Cousin = make_shared<node>("堂妹");
        F_Y_B_O_B_Cousin = make_shared<node>("堂兄");
        F_Y_B_Y_B_Cousin = make_shared<node>("堂弟");
        F_Y_B_O_G_Cousin = make_shared<node>("堂姊");
        F_Y_B_Y_G_Cousin = make_shared<node>("堂妹");

        FG_Uncle = make_shared<node>("姑丈");
        FG_Aunt = make_shared<node>("姑媽");
        F_G_O_B_Cousin = make_shared<node>("表兄");
        F_G_Y_B_Cousin = make_shared<node>("表弟");
        F_G_O_G_Cousin = make_shared<node>("表姊");
        F_G_Y_G_Cousin = make_shared<node>("表妹");

        F_GrandFather = make_shared<node>("祖父");
        F_GrandMother = make_shared<node>("祖母");
        M_GrandFather = make_shared<node>("外祖父");
        M_GrandMother = make_shared<node>("外祖母");

        M_B_Uncle = make_shared<node>("舅舅");
        M_B_Aunt = make_shared<node>("舅媽");
        M_B_O_B_Cousin = make_shared<node>("表兄");
        M_B_Y__B_Cousin = make_shared<node>("表弟");
        M_B_O_G_Cousin = make_shared<node>("表姊");
        M_B_Y_G_Cousin = make_shared<node>("表妹");

        MG_Uncle = make_shared<node>("姨丈");
        MG_Aunt = make_shared<node>("姨媽");
        M_G_O_B_Cousin = make_shared<node>("表兄");
        M_G_Y_B_Cousin = make_shared<node>("表弟");
        M_G_O_G_Cousin = make_shared<node>("表姊");
        M_G_Y_G_Cousin = make_shared<node>("表妹");

        Husband_Father = make_shared<node>("夫父");
        Husband_Mother = make_shared<node>("夫母");

        Husband_O_Brother = make_shared<node>("夫兄");
        Husband_O_Brother_W = make_shared<node>("夫兄嫂");
        Husband_Y_Brother = make_shared<node>("夫弟");
        Husband_Y_Brother_W = make_shared<node>("夫弟媳");
        Husband_O_Brother_Nephew = make_shared<node>("姪子");
        Husband_O_Brother_Concubine = make_shared<node>("姪女");
        Husband_Y_Brother_Nephew = make_shared<node>("姪子");
        Husband_Y_Brother_Concubine = make_shared<node>("姪女");

        Husband_O_Sister = make_shared<node>("夫姊");
        Husband_O_Sister_H = make_shared<node>("夫姊夫");
        Husband_Y_Sister = make_shared<node>("夫妹");
        Husband_Y_Sister_H = make_shared<node>("夫妹夫");
        Husband_O_Sister_Nephew = make_shared<node>("外甥");
        Husband_O_Sister_Concubine = make_shared<node>("外甥女");
        Husband_Y_Sister_Nephew = make_shared<node>("外甥");
        Husband_Y_Sister_Concubine = make_shared<node>("外甥女");

        Wife_Father = make_shared<node>("妻父");
        Wife_Mother = make_shared<node>("妻母");

        Wife_O_Brother = make_shared<node>("妻兄");
        Wife_O_Brother_W = make_shared<node>("妻兄嫂");
        Wife_Y_Brother = make_shared<node>("妻弟");
        Wife_Y_Brother_W = make_shared<node>("妻弟媳");

        Wife_O_Sister = make_shared<node>("妻姊");
        Wife_O_Sister_H = make_shared<node>("妻姊夫");
        Wife_Y_Sister = make_shared<node>("妻妹");
        Wife_Y_Sister_H = make_shared<node>("妻妹夫");
        Wife_B_Nephew = make_shared<node>("外甥");
        Wife_Bo_Concubine = make_shared<node>("外甥女");
        Wife_By_Nephew = make_shared<node>("外甥");
        Wife_By_Concubine = make_shared<node>("外甥女");
        Wife_G_O_Nephew = make_shared<node>("外甥");
        Wife_G_O_Concubine = make_shared<node>("外甥女");
        Wife_G_Y_Nephew = make_shared<node>("外甥");
        Wife_G_Y_Concubine = make_shared<node>("外甥女");
    }

    void buildEdges()
    {
        root->edges[L"爸爸"] = father;
        root->edges[L"媽媽"] = mother;
        root->edges[L"哥哥"] = OlderBrother;
        root->edges[L"弟弟"] = YoungerBrother;
        root->edges[L"姊姊"] = OlderSister;
        root->edges[L"妹妹"] = YoungerSister;
        root->edges[L"兒子"] = B_Son;
        root->edges[L"兒子(較年輕)"] = B_Son;
        root->edges[L"兒子(較年長)"] = B_Son;
        root->edges[L"女兒"] = B_Daughter;
        root->edges[L"女兒(較年輕)"] = B_Daughter;
        root->edges[L"女兒(較年長)"] = B_Daughter;
        root->edges[L"妻子"] = wife;
        root->edges[L"丈夫"] = husband;
        root->edges[L"我"] = root;
        root->edges[L"我(男)"] = MB;
        root->edges[L"我(女)"] = MG;

        MB->edges[L"爸爸"] = father;
        MB->edges[L"媽媽"] = mother;
        MB->edges[L"哥哥"] = OlderBrother;
        MB->edges[L"弟弟"] = YoungerBrother;
        MB->edges[L"姊姊"] = OlderSister;
        MB->edges[L"妹妹"] = YoungerSister;
        MB->edges[L"兒子"] = B_Son;
        MB->edges[L"兒子(較年長)"] = B_Son;
        MB->edges[L"兒子(較年輕)"] = B_Son;
        MB->edges[L"女兒"] = B_Daughter;
        MB->edges[L"女兒(較年長)"] = B_Daughter;
        MB->edges[L"女兒(較年輕)"] = B_Daughter;
        MB->edges[L"妻子"] = wife;
        MB->edges[L"丈夫"] = husband;
        MB->edges[L"我"] = MB;

        MG->edges[L"爸爸"] = father;
        MG->edges[L"媽媽"] = mother;
        MG->edges[L"哥哥"] = OlderBrother;
        MG->edges[L"弟弟"] = YoungerBrother;
        MG->edges[L"姊姊"] = OlderSister;
        MG->edges[L"妹妹"] = YoungerSister;
        MG->edges[L"兒子"] = G_Son;
        MG->edges[L"兒子(較年長)"] = G_Son;
        MG->edges[L"兒子(較年輕)"] = G_Son;
        MG->edges[L"女兒"] = G_Daughter;
        MG->edges[L"女兒(較年長)"] = G_Daughter;
        MG->edges[L"女兒(較年輕)"] = G_Daughter;
        MG->edges[L"妻子"] = wife;
        MG->edges[L"丈夫"] = husband;
        MG->edges[L"我"] = MG;

        father->edges[L"爸爸"] = F_GrandFather;
        father->edges[L"媽媽"] = F_GrandMother;
        father->edges[L"哥哥"] = F_B_Uncle;
        father->edges[L"弟弟"] = F_B_Y_Uncle;
        father->edges[L"姊姊"] = FG_Aunt;
        father->edges[L"妹妹"] = FG_Aunt;
        father->edges[L"妻子"] = mother;
        father->edges[L"兒子(較年長)"] = OlderBrother;
        father->edges[L"兒子(較年輕)"] = YoungerBrother;
        father->edges[L"兒子"] = YoungerBrother;
        father->edges[L"女兒(較年長)"] = OlderSister;
        father->edges[L"女兒(較年輕)"] = YoungerSister;
        father->edges[L"女兒"] = YoungerSister;

        mother->edges[L"爸爸"] = M_GrandFather;
        mother->edges[L"媽媽"] = M_GrandMother;
        mother->edges[L"哥哥"] = M_B_Uncle;
        mother->edges[L"弟弟"] = M_B_Uncle;
        mother->edges[L"姊姊"] = MG_Aunt;
        mother->edges[L"妹妹"] = MG_Aunt;
        mother->edges[L"丈夫"] = father;
        mother->edges[L"兒子(較年長)"] = OlderBrother;
        mother->edges[L"兒子(較年輕)"] = YoungerBrother;
        mother->edges[L"兒子"] = YoungerBrother;
        mother->edges[L"女兒(較年長)"] = OlderSister;
        mother->edges[L"女兒(較年輕)"] = YoungerSister;
        mother->edges[L"女兒"] = YoungerSister;

        OlderBrother->edges[L"爸爸"] = father;
        OlderBrother->edges[L"媽媽"] = mother;
        OlderBrother->edges[L"哥哥"] = OlderBrother;
        OlderBrother->edges[L"弟弟"] = YoungerBrother;
        OlderBrother->edges[L"姊姊"] = OlderSister;
        OlderBrother->edges[L"妹妹"] = YoungerSister;
        OlderBrother->edges[L"妹妹(較年輕)"] = YoungerSister;
        OlderBrother->edges[L"妻子"] = O_SIL;
        OlderBrother->edges[L"兒子(較年長)"] = O_B_Nephew;
        OlderBrother->edges[L"兒子(較年輕)"] = O_B_Nephew;
        OlderBrother->edges[L"兒子"] = O_B_Nephew;
        OlderBrother->edges[L"女兒(較年長)"] = O_B_Concubine;
        OlderBrother->edges[L"女兒(較年輕)"] = O_B_Concubine;
        OlderBrother->edges[L"女兒"] = O_B_Concubine;

        YoungerBrother->edges[L"爸爸"] = father;
        YoungerBrother->edges[L"媽媽"] = mother;
        YoungerBrother->edges[L"哥哥"] = OlderBrother;
        YoungerBrother->edges[L"弟弟"] = YoungerBrother;
        YoungerBrother->edges[L"姊姊"] = OlderSister;
        YoungerBrother->edges[L"妹妹"] = YoungerSister;
        YoungerBrother->edges[L"妻子"] = Y_SIL;
        YoungerBrother->edges[L"兒子(較年長)"] = Y_B_Nephew;
        YoungerBrother->edges[L"兒子(較年輕)"] = Y_B_Nephew;
        YoungerBrother->edges[L"兒子"] = Y_B_Nephew;
        YoungerBrother->edges[L"女兒(較年長)"] = Y_B_Concubine;
        YoungerBrother->edges[L"女兒(較年輕)"] = Y_B_Concubine;
        YoungerBrother->edges[L"女兒"] = Y_B_Concubine;

        OlderSister->edges[L"爸爸"] = father;
        OlderSister->edges[L"媽媽"] = mother;
        OlderSister->edges[L"哥哥"] = OlderBrother;
        OlderSister->edges[L"弟弟"] = YoungerBrother;
        OlderSister->edges[L"姊姊"] = OlderSister;
        OlderSister->edges[L"妹妹"] = YoungerSister;
        OlderSister->edges[L"丈夫"] = O_BIL;
        OlderSister->edges[L"兒子(較年長)"] = O_Sis_Nephew;
        OlderSister->edges[L"兒子(較年輕)"] = O_Sis_Nephew;
        OlderSister->edges[L"兒子"] = O_Sis_Nephew;
        OlderSister->edges[L"女兒(較年長)"] = O_Sis_Concubine;
        OlderSister->edges[L"女兒(較年輕)"] = O_Sis_Concubine;
        OlderSister->edges[L"女兒"] = O_Sis_Concubine;

        YoungerSister->edges[L"爸爸"] = father;
        YoungerSister->edges[L"媽媽"] = mother;
        YoungerSister->edges[L"哥哥"] = OlderBrother;
        YoungerSister->edges[L"弟弟"] = YoungerBrother;
        YoungerSister->edges[L"姊姊"] = OlderSister;
        YoungerSister->edges[L"妹妹"] = YoungerSister;
        YoungerSister->edges[L"丈夫"] = Y_BIL;
        YoungerSister->edges[L"兒子(較年長)"] = Y_Sis_Nephew;
        YoungerSister->edges[L"兒子(較年輕)"] = Y_Sis_Nephew;
        YoungerSister->edges[L"兒子"] = Y_Sis_Nephew;
        YoungerSister->edges[L"女兒(較年長)"] = Y_Sis_Concubine;
        YoungerSister->edges[L"女兒(較年輕)"] = Y_Sis_Concubine;
        YoungerSister->edges[L"女兒"] = Y_Sis_Concubine;

        wife->edges[L"爸爸"] = Wife_Father;
        wife->edges[L"媽媽"] = Wife_Mother;
        wife->edges[L"哥哥"] = Wife_O_Brother;
        wife->edges[L"弟弟"] = Wife_Y_Brother;
        wife->edges[L"姊姊"] = Wife_O_Sister;
        wife->edges[L"妹妹"] = Wife_Y_Sister;
        wife->edges[L"丈夫"] = root;
        wife->edges[L"兒子(較年長)"] = B_Son;
        wife->edges[L"兒子(較年輕)"] = B_Son;
        wife->edges[L"兒子"] = B_Son;
        wife->edges[L"女兒(較年長)"] = B_Daughter;
        wife->edges[L"女兒(較年輕)"] = B_Daughter;
        wife->edges[L"女兒"] = B_Daughter;

        husband->edges[L"爸爸"] = Husband_Father;
        husband->edges[L"媽媽"] = Husband_Mother;
        husband->edges[L"哥哥"] = Husband_O_Brother;
        husband->edges[L"弟弟"] = Husband_Y_Brother;
        husband->edges[L"姊姊"] = Husband_O_Sister;
        husband->edges[L"妹妹"] = Husband_Y_Sister;
        husband->edges[L"妻子"] = root;
        husband->edges[L"兒子(較年長)"] = G_Son;
        husband->edges[L"兒子(較年輕)"] = G_Son;
        husband->edges[L"兒子"] = G_Son;
        husband->edges[L"女兒(較年長)"] = G_Daughter;
        husband->edges[L"女兒(較年輕)"] = G_Daughter;
        husband->edges[L"女兒"] = G_Daughter;

        F_GrandFather->edges[L"妻子"] = F_GrandMother;
        F_GrandFather->edges[L"兒子(較年長)"] = F_B_Uncle;
        F_GrandFather->edges[L"兒子(較年輕)"] = F_B_Y_Uncle;
        F_GrandFather->edges[L"兒子"] = father;
        F_GrandFather->edges[L"女兒(較年長)"] = FG_Aunt;
        F_GrandFather->edges[L"女兒(較年輕)"] = FG_Aunt;
        F_GrandFather->edges[L"女兒"] = FG_Aunt;

        F_GrandMother->edges[L"丈夫"] = F_GrandFather;
        F_GrandMother->edges[L"兒子(較年長)"] = F_B_Uncle;
        F_GrandMother->edges[L"兒子(較年輕)"] = F_B_Y_Uncle;
        F_GrandMother->edges[L"兒子"] = father;
        F_GrandMother->edges[L"女兒(較年長)"] = FG_Aunt;
        F_GrandMother->edges[L"女兒(較年輕)"] = FG_Aunt;
        F_GrandMother->edges[L"女兒"] = FG_Aunt;

        M_GrandFather->edges[L"妻子"] = M_GrandMother;
        M_GrandFather->edges[L"兒子(較年長)"] = M_B_Uncle;
        M_GrandFather->edges[L"兒子(較年輕)"] = M_B_Uncle;
        M_GrandFather->edges[L"兒子"] = M_B_Uncle;
        M_GrandFather->edges[L"女兒(較年長)"] = MG_Aunt;
        M_GrandFather->edges[L"女兒(較年輕)"] = MG_Aunt;
        M_GrandFather->edges[L"女兒"] = MG_Aunt;

        M_GrandMother->edges[L"丈夫"] = M_GrandFather;
        M_GrandMother->edges[L"兒子(較年長)"] = M_B_Uncle;
        M_GrandMother->edges[L"兒子(較年輕)"] = M_B_Uncle;
        M_GrandMother->edges[L"兒子"] = M_B_Uncle;
        M_GrandMother->edges[L"女兒(較年長)"] = MG_Aunt;
        M_GrandMother->edges[L"女兒(較年輕)"] = MG_Aunt;
        M_GrandMother->edges[L"女兒"] = MG_Aunt;

        FG_Aunt->edges[L"爸爸"] = F_GrandFather;
        FG_Aunt->edges[L"媽媽"] = F_GrandMother;
        FG_Aunt->edges[L"丈夫"] = FG_Uncle;
        FG_Aunt->edges[L"哥哥"] = F_B_Uncle;
        FG_Aunt->edges[L"弟弟"] = F_B_Y_Uncle;
        FG_Aunt->edges[L"姊姊"] = FG_Aunt;
        FG_Aunt->edges[L"妹妹"] = FG_Aunt;
        FG_Aunt->edges[L"兒子(較年長)"] = F_G_O_B_Cousin;
        FG_Aunt->edges[L"兒子(較年輕)"] = F_G_Y_B_Cousin;
        FG_Aunt->edges[L"兒子"] = F_G_Y_B_Cousin;
        FG_Aunt->edges[L"女兒(較年長)"] = F_G_O_G_Cousin;
        FG_Aunt->edges[L"女兒(較年輕)"] = F_G_Y_G_Cousin;
        FG_Aunt->edges[L"女兒"] = F_G_Y_G_Cousin;

        FG_Uncle->edges[L"妻子"] = FG_Aunt;
        FG_Uncle->edges[L"兒子(較年長)"] = F_G_O_B_Cousin;
        FG_Uncle->edges[L"兒子(較年輕)"] = F_G_Y_B_Cousin;
        FG_Uncle->edges[L"兒子"] = F_G_Y_B_Cousin;
        FG_Uncle->edges[L"女兒(較年長)"] = F_G_O_G_Cousin;
        FG_Uncle->edges[L"女兒(較年輕)"] = F_G_Y_G_Cousin;
        FG_Uncle->edges[L"女兒"] = F_G_Y_G_Cousin;

        F_B_Y_Uncle->edges[L"爸爸"] = F_GrandFather;
        F_B_Y_Uncle->edges[L"媽媽"] = F_GrandMother;
        F_B_Y_Uncle->edges[L"哥哥"] = F_B_Uncle;
        F_B_Y_Uncle->edges[L"弟弟"] = F_B_Y_Uncle;
        F_B_Y_Uncle->edges[L"姊姊"] = FG_Aunt;
        F_B_Y_Uncle->edges[L"妹妹"] = FG_Aunt;
        F_B_Y_Uncle->edges[L"妻子"] = F_B_Y_Aunt;
        F_B_Y_Uncle->edges[L"兒子(較年長)"] = F_Y_B_O_B_Cousin;
        F_B_Y_Uncle->edges[L"兒子(較年輕)"] = F_Y_B_Y_B_Cousin;
        F_B_Y_Uncle->edges[L"兒子"] = F_Y_B_Y_B_Cousin;
        F_B_Y_Uncle->edges[L"女兒(較年長)"] = F_Y_B_O_G_Cousin;
        F_B_Y_Uncle->edges[L"女兒(較年輕)"] = F_Y_B_Y_G_Cousin;
        F_B_Y_Uncle->edges[L"女兒"] = F_Y_B_Y_G_Cousin;

        F_B_Y_Aunt->edges[L"丈夫"] = F_B_Y_Uncle;
        F_B_Y_Aunt->edges[L"兒子(較年長)"] = F_Y_B_O_B_Cousin;
        F_B_Y_Aunt->edges[L"兒子(較年輕)"] = F_Y_B_Y_B_Cousin;
        F_B_Y_Aunt->edges[L"兒子"] = F_Y_B_Y_B_Cousin;
        F_B_Y_Aunt->edges[L"女兒(較年長)"] = F_Y_B_O_G_Cousin;
        F_B_Y_Aunt->edges[L"女兒(較年輕)"] = F_Y_B_Y_G_Cousin;
        F_B_Y_Aunt->edges[L"女兒"] = F_Y_B_Y_G_Cousin;

        F_B_Uncle->edges[L"爸爸"] = F_GrandFather;
        F_B_Uncle->edges[L"媽媽"] = F_GrandMother;
        F_B_Uncle->edges[L"哥哥"] = F_B_Uncle;
        F_B_Uncle->edges[L"弟弟"] = F_B_Y_Uncle;
        F_B_Uncle->edges[L"姊姊"] = FG_Aunt;
        F_B_Uncle->edges[L"妹妹"] = FG_Aunt;
        F_B_Uncle->edges[L"妻子"] = F_B_O_Aunt;
        F_B_Uncle->edges[L"兒子(較年長)"] = F_O_B_O_B_Cousin;
        F_B_Uncle->edges[L"兒子(較年輕)"] = F_O_B_Y_B_Cousin;
        F_B_Uncle->edges[L"兒子"] = F_O_B_Y_B_Cousin;
        F_B_Uncle->edges[L"女兒(較年長)"] = F_O_B_O_G_Cousin;
        F_B_Uncle->edges[L"女兒(較年輕)"] = F_O_B_Y_G_Cousin;
        F_B_Uncle->edges[L"女兒"] = F_O_B_Y_G_Cousin;

        F_B_O_Aunt->edges[L"丈夫"] = F_B_Uncle;
        F_B_O_Aunt->edges[L"兒子(較年長)"] = F_O_B_O_B_Cousin;
        F_B_O_Aunt->edges[L"兒子(較年輕)"] = F_O_B_Y_B_Cousin;
        F_B_O_Aunt->edges[L"兒子"] = F_O_B_Y_B_Cousin;
        F_B_O_Aunt->edges[L"女兒(較年長)"] = F_O_B_O_G_Cousin;
        F_B_O_Aunt->edges[L"女兒(較年輕)"] = F_O_B_Y_G_Cousin;
        F_B_O_Aunt->edges[L"女兒"] = F_O_B_Y_G_Cousin;

        M_B_Uncle->edges[L"爸爸"] = M_GrandFather;
        M_B_Uncle->edges[L"媽媽"] = M_GrandMother;
        M_B_Uncle->edges[L"哥哥"] = M_B_Uncle;
        M_B_Uncle->edges[L"弟弟"] = M_B_Uncle;
        M_B_Uncle->edges[L"姊姊"] = MG_Aunt;
        M_B_Uncle->edges[L"妹妹"] = MG_Aunt;
        M_B_Uncle->edges[L"妻子"] = M_B_Aunt;
        M_B_Uncle->edges[L"兒子(較年長)"] = M_B_O_B_Cousin;
        M_B_Uncle->edges[L"兒子(較年輕)"] = M_B_Y__B_Cousin;
        M_B_Uncle->edges[L"兒子"] = M_B_Y__B_Cousin;
        M_B_Uncle->edges[L"女兒(較年長)"] = M_B_O_G_Cousin;
        M_B_Uncle->edges[L"女兒(較年輕)"] = M_B_Y_G_Cousin;
        M_B_Uncle->edges[L"女兒"] = M_B_Y_G_Cousin;

        M_B_Aunt->edges[L"丈夫"] = M_B_Uncle;
        M_B_Aunt->edges[L"兒子(較年長)"] = M_B_O_B_Cousin;
        M_B_Aunt->edges[L"兒子(較年輕)"] = M_B_Y__B_Cousin;
        M_B_Aunt->edges[L"兒子"] = M_B_Y__B_Cousin;
        M_B_Aunt->edges[L"女兒(較年長)"] = M_B_O_G_Cousin;
        M_B_Aunt->edges[L"女兒(較年輕)"] = M_B_Y_G_Cousin;
        M_B_Aunt->edges[L"女兒"] = M_B_Y_G_Cousin;

        MG_Aunt->edges[L"爸爸"] = M_GrandFather;
        MG_Aunt->edges[L"媽媽"] = M_GrandMother;
        MG_Aunt->edges[L"丈夫"] = MG_Uncle;
        MG_Aunt->edges[L"哥哥"] = M_B_Uncle;
        MG_Aunt->edges[L"弟弟"] = M_B_Uncle;
        MG_Aunt->edges[L"姊姊"] = MG_Aunt;
        MG_Aunt->edges[L"妹妹"] = MG_Aunt;
        MG_Aunt->edges[L"兒子(較年長)"] = M_G_O_B_Cousin;
        MG_Aunt->edges[L"兒子(較年輕)"] = M_G_Y_B_Cousin;
        MG_Aunt->edges[L"兒子"] = M_G_Y_B_Cousin;
        MG_Aunt->edges[L"女兒(較年長)"] = M_G_O_G_Cousin;
        MG_Aunt->edges[L"女兒(較年輕)"] = M_G_Y_G_Cousin;
        MG_Aunt->edges[L"女兒"] = M_G_Y_G_Cousin;

        MG_Uncle->edges[L"妻子"] = MG_Aunt;
        MG_Uncle->edges[L"兒子(較年長)"] = M_G_O_B_Cousin;
        MG_Uncle->edges[L"兒子(較年輕)"] = M_G_Y_B_Cousin;
        MG_Uncle->edges[L"兒子"] = M_G_Y_B_Cousin;
        MG_Uncle->edges[L"女兒(較年長)"] = M_G_O_G_Cousin;
        MG_Uncle->edges[L"女兒(較年輕)"] = M_G_Y_G_Cousin;
        MG_Uncle->edges[L"女兒"] = M_G_Y_G_Cousin;

        F_G_O_B_Cousin->edges[L"爸爸"] = FG_Uncle;
        F_G_O_B_Cousin->edges[L"媽媽"] = FG_Aunt;
        F_G_O_B_Cousin->edges[L"哥哥"] = F_G_O_B_Cousin;
        F_G_O_B_Cousin->edges[L"弟弟"] = F_G_Y_B_Cousin;
        F_G_O_B_Cousin->edges[L"姊姊"] = F_G_O_G_Cousin;
        F_G_O_B_Cousin->edges[L"妹妹"] = F_G_Y_G_Cousin;

        F_G_Y_B_Cousin->edges[L"爸爸"] = FG_Uncle;
        F_G_Y_B_Cousin->edges[L"媽媽"] = FG_Aunt;
        F_G_Y_B_Cousin->edges[L"哥哥"] = F_G_O_B_Cousin;
        F_G_Y_B_Cousin->edges[L"弟弟"] = F_G_Y_B_Cousin;
        F_G_Y_B_Cousin->edges[L"姊姊"] = F_G_O_G_Cousin;
        F_G_Y_B_Cousin->edges[L"妹妹"] = F_G_Y_G_Cousin;

        F_G_O_G_Cousin->edges[L"爸爸"] = FG_Uncle;
        F_G_O_G_Cousin->edges[L"媽媽"] = FG_Aunt;
        F_G_O_G_Cousin->edges[L"哥哥"] = F_G_O_B_Cousin;
        F_G_O_G_Cousin->edges[L"弟弟"] = F_G_Y_B_Cousin;
        F_G_O_G_Cousin->edges[L"姊姊"] = F_G_O_G_Cousin;
        F_G_O_G_Cousin->edges[L"妹妹"] = F_G_Y_G_Cousin;

        F_G_Y_G_Cousin->edges[L"爸爸"] = FG_Uncle;
        F_G_Y_G_Cousin->edges[L"媽媽"] = FG_Aunt;
        F_G_Y_G_Cousin->edges[L"哥哥"] = F_G_O_B_Cousin;
        F_G_Y_G_Cousin->edges[L"弟弟"] = F_G_Y_B_Cousin;
        F_G_Y_G_Cousin->edges[L"妹妹"] = F_G_Y_G_Cousin;
        F_G_Y_G_Cousin->edges[L"姊姊"] = F_G_O_G_Cousin;

        F_Y_B_O_B_Cousin->edges[L"爸爸"] = F_B_Y_Uncle;
        F_Y_B_O_B_Cousin->edges[L"媽媽"] = F_B_Y_Aunt;
        F_Y_B_O_B_Cousin->edges[L"哥哥"] = F_Y_B_O_B_Cousin;
        F_Y_B_O_B_Cousin->edges[L"弟弟"] = F_Y_B_Y_B_Cousin;
        F_Y_B_O_B_Cousin->edges[L"姊姊"] = F_Y_B_O_G_Cousin;
        F_Y_B_O_B_Cousin->edges[L"妹妹"] = F_Y_B_Y_G_Cousin;

        F_Y_B_Y_B_Cousin->edges[L"爸爸"] = F_B_Y_Uncle;
        F_Y_B_Y_B_Cousin->edges[L"媽媽"] = F_B_Y_Aunt;
        F_Y_B_Y_B_Cousin->edges[L"哥哥"] = F_Y_B_O_B_Cousin;
        F_Y_B_Y_B_Cousin->edges[L"弟弟"] = F_Y_B_Y_B_Cousin;
        F_Y_B_Y_B_Cousin->edges[L"姊姊"] = F_Y_B_O_G_Cousin;
        F_Y_B_Y_B_Cousin->edges[L"妹妹"] = F_Y_B_Y_G_Cousin;

        F_Y_B_O_G_Cousin->edges[L"爸爸"] = F_B_Y_Uncle;
        F_Y_B_O_G_Cousin->edges[L"媽媽"] = F_B_Y_Aunt;
        F_Y_B_O_G_Cousin->edges[L"弟弟"] = F_Y_B_Y_B_Cousin;
        F_Y_B_O_G_Cousin->edges[L"哥哥"] = F_Y_B_O_B_Cousin;
        F_Y_B_O_G_Cousin->edges[L"姊姊"] = F_Y_B_O_G_Cousin;
        F_Y_B_O_G_Cousin->edges[L"妹妹"] = F_Y_B_Y_G_Cousin;

        F_Y_B_Y_G_Cousin->edges[L"爸爸"] = F_B_Y_Uncle;
        F_Y_B_Y_G_Cousin->edges[L"媽媽"] = F_B_Y_Aunt;
        F_Y_B_Y_G_Cousin->edges[L"弟弟"] = F_Y_B_Y_B_Cousin;
        F_Y_B_Y_G_Cousin->edges[L"哥哥"] = F_Y_B_O_B_Cousin;
        F_Y_B_Y_G_Cousin->edges[L"姊姊"] = F_Y_B_O_G_Cousin;
        F_Y_B_Y_G_Cousin->edges[L"妹妹"] = F_Y_B_Y_G_Cousin;

        F_O_B_O_B_Cousin->edges[L"爸爸"] = F_B_Uncle;
        F_O_B_O_B_Cousin->edges[L"媽媽"] = F_B_O_Aunt;
        F_O_B_O_B_Cousin->edges[L"哥哥"] = F_O_B_O_B_Cousin;
        F_O_B_O_B_Cousin->edges[L"弟弟"] = F_O_B_Y_B_Cousin;
        F_O_B_O_B_Cousin->edges[L"姊姊"] = F_O_B_O_G_Cousin;
        F_O_B_O_B_Cousin->edges[L"妹妹"] = F_O_B_Y_G_Cousin;

        F_O_B_Y_B_Cousin->edges[L"爸爸"] = F_B_Uncle;
        F_O_B_Y_B_Cousin->edges[L"媽媽"] = F_B_O_Aunt;
        F_O_B_Y_B_Cousin->edges[L"哥哥"] = F_O_B_O_B_Cousin;
        F_O_B_Y_B_Cousin->edges[L"弟弟"] = F_O_B_Y_B_Cousin;
        F_O_B_Y_B_Cousin->edges[L"姊姊"] = F_O_B_O_G_Cousin;
        F_O_B_Y_B_Cousin->edges[L"妹妹"] = F_O_B_Y_G_Cousin;

        F_O_B_O_G_Cousin->edges[L"爸爸"] = F_B_Uncle;
        F_O_B_O_G_Cousin->edges[L"媽媽"] = F_B_O_Aunt;
        F_O_B_O_G_Cousin->edges[L"弟弟"] = F_O_B_Y_B_Cousin;
        F_O_B_O_G_Cousin->edges[L"哥哥"] = F_O_B_O_B_Cousin;
        F_O_B_O_G_Cousin->edges[L"妹妹"] = F_O_B_Y_G_Cousin;
        F_O_B_O_G_Cousin->edges[L"姊姊"] = F_O_B_O_G_Cousin;

        F_O_B_Y_G_Cousin->edges[L"爸爸"] = F_B_Uncle;
        F_O_B_Y_G_Cousin->edges[L"媽媽"] = F_B_O_Aunt;
        F_O_B_Y_G_Cousin->edges[L"弟弟"] = F_O_B_Y_B_Cousin;
        F_O_B_Y_G_Cousin->edges[L"哥哥"] = F_O_B_O_B_Cousin;
        F_O_B_Y_G_Cousin->edges[L"姊姊"] = F_O_B_O_G_Cousin;
        F_O_B_Y_G_Cousin->edges[L"妹妹"] = F_O_B_Y_G_Cousin;

        O_SIL->edges[L"丈夫"] = OlderBrother;
        O_SIL->edges[L"兒子(較年長)"] = O_B_Nephew;
        O_SIL->edges[L"兒子(較年輕)"] = O_B_Nephew;
        O_SIL->edges[L"兒子"] = O_B_Nephew;
        O_SIL->edges[L"女兒(較年長)"] = O_B_Concubine;
        O_SIL->edges[L"女兒(較年輕)"] = O_B_Concubine;
        O_SIL->edges[L"女兒"] = O_B_Concubine;

        Y_SIL->edges[L"丈夫"] = YoungerBrother;
        Y_SIL->edges[L"兒子(較年長)"] = Y_B_Nephew;
        Y_SIL->edges[L"兒子(較年輕)"] = Y_B_Nephew;
        Y_SIL->edges[L"兒子"] = Y_B_Nephew;
        Y_SIL->edges[L"女兒(較年長)"] = Y_B_Concubine;
        Y_SIL->edges[L"女兒(較年輕)"] = Y_B_Concubine;
        Y_SIL->edges[L"女兒"] = Y_B_Concubine;

        O_B_Nephew->edges[L"爸爸"] = OlderBrother;
        O_B_Nephew->edges[L"媽媽"] = O_SIL;
        O_B_Nephew->edges[L"哥哥"] = O_B_Nephew;
        O_B_Nephew->edges[L"弟弟"] = O_B_Nephew;
        O_B_Nephew->edges[L"妹妹"] = O_B_Concubine;
        O_B_Nephew->edges[L"姊姊"] = O_B_Concubine;

        O_B_Concubine->edges[L"爸爸"] = OlderBrother;
        O_B_Concubine->edges[L"媽媽"] = O_SIL;
        O_B_Concubine->edges[L"哥哥"] = O_B_Nephew;
        O_B_Concubine->edges[L"弟弟"] = O_B_Nephew;
        O_B_Concubine->edges[L"姊姊"] = O_B_Concubine;
        O_B_Concubine->edges[L"妹妹"] = O_B_Concubine;

        Y_B_Nephew->edges[L"爸爸"] = YoungerBrother;
        Y_B_Nephew->edges[L"媽媽"] = Y_SIL;
        Y_B_Nephew->edges[L"哥哥"] = Y_B_Nephew;
        Y_B_Nephew->edges[L"弟弟"] = Y_B_Nephew;
        Y_B_Nephew->edges[L"妹妹"] = Y_B_Concubine;
        Y_B_Nephew->edges[L"姊姊"] = Y_B_Concubine;

        Y_B_Concubine->edges[L"爸爸"] = YoungerBrother;
        Y_B_Concubine->edges[L"媽媽"] = Y_SIL;
        Y_B_Concubine->edges[L"哥哥"] = Y_B_Nephew;
        Y_B_Concubine->edges[L"弟弟"] = Y_B_Nephew;
        Y_B_Concubine->edges[L"姊姊"] = Y_B_Concubine;
        Y_B_Concubine->edges[L"妹妹"] = Y_B_Concubine;

        O_BIL->edges[L"妻子"] = OlderSister;
        O_BIL->edges[L"兒子(較年長)"] = O_Sis_Nephew;
        O_BIL->edges[L"兒子(較年輕)"] = O_Sis_Nephew;
        O_BIL->edges[L"兒子"] = O_Sis_Nephew;
        O_BIL->edges[L"女兒(較年長)"] = O_Sis_Concubine;
        O_BIL->edges[L"女兒(較年輕)"] = O_Sis_Concubine;
        O_BIL->edges[L"女兒"] = O_Sis_Concubine;

        Y_BIL->edges[L"妻子"] = YoungerSister;
        Y_BIL->edges[L"兒子(較年長)"] = Y_Sis_Nephew;
        Y_BIL->edges[L"兒子(較年輕)"] = Y_Sis_Nephew;
        Y_BIL->edges[L"兒子"] = Y_Sis_Nephew;
        Y_BIL->edges[L"女兒(較年長)"] = Y_Sis_Concubine;
        Y_BIL->edges[L"女兒(較年輕)"] = Y_Sis_Concubine;
        Y_BIL->edges[L"女兒"] = Y_Sis_Concubine;

        O_Sis_Nephew->edges[L"爸爸"] = O_BIL;
        O_Sis_Nephew->edges[L"媽媽"] = OlderSister;
        O_Sis_Nephew->edges[L"哥哥"] = O_Sis_Nephew;
        O_Sis_Nephew->edges[L"弟弟"] = O_Sis_Nephew;
        O_Sis_Nephew->edges[L"姊姊"] = O_Sis_Concubine;
        O_Sis_Nephew->edges[L"妹妹"] = O_Sis_Concubine;

        O_Sis_Concubine->edges[L"爸爸"] = O_BIL;
        O_Sis_Concubine->edges[L"媽媽"] = OlderSister;
        O_Sis_Concubine->edges[L"哥哥"] = O_Sis_Nephew;
        O_Sis_Concubine->edges[L"弟弟"] = O_Sis_Nephew;
        O_Sis_Concubine->edges[L"姊姊"] = O_Sis_Concubine;
        O_Sis_Concubine->edges[L"妹妹"] = O_Sis_Concubine;

        Y_Sis_Nephew->edges[L"爸爸"] = Y_BIL;
        Y_Sis_Nephew->edges[L"媽媽"] = YoungerSister;
        Y_Sis_Nephew->edges[L"哥哥"] = Y_Sis_Nephew;
        Y_Sis_Nephew->edges[L"弟弟"] = Y_Sis_Nephew;
        Y_Sis_Nephew->edges[L"姊姊"] = Y_Sis_Concubine;
        Y_Sis_Nephew->edges[L"妹妹"] = Y_Sis_Concubine;

        Y_Sis_Concubine->edges[L"爸爸"] = Y_BIL;
        Y_Sis_Concubine->edges[L"媽媽"] = YoungerSister;
        Y_Sis_Concubine->edges[L"哥哥"] = Y_Sis_Nephew;
        Y_Sis_Concubine->edges[L"弟弟"] = Y_Sis_Nephew;
        Y_Sis_Concubine->edges[L"姊姊"] = Y_Sis_Concubine;
        Y_Sis_Concubine->edges[L"妹妹"] = Y_Sis_Concubine;

        M_B_O_B_Cousin->edges[L"爸爸"] = M_B_Uncle;
        M_B_O_B_Cousin->edges[L"媽媽"] = M_B_Aunt;
        M_B_O_B_Cousin->edges[L"哥哥"] = M_B_O_B_Cousin;
        M_B_O_B_Cousin->edges[L"弟弟"] = M_B_Y__B_Cousin;
        M_B_O_B_Cousin->edges[L"姊姊"] = M_B_O_G_Cousin;
        M_B_O_B_Cousin->edges[L"妹妹"] = M_B_Y_G_Cousin;

        M_B_Y__B_Cousin->edges[L"爸爸"] = M_B_Uncle;
        M_B_Y__B_Cousin->edges[L"媽媽"] = M_B_Aunt;
        M_B_Y__B_Cousin->edges[L"哥哥"] = M_B_O_B_Cousin;
        M_B_Y__B_Cousin->edges[L"弟弟"] = M_B_Y__B_Cousin;
        M_B_Y__B_Cousin->edges[L"姊姊"] = M_B_O_G_Cousin;
        M_B_Y__B_Cousin->edges[L"妹妹"] = M_B_Y_G_Cousin;

        M_B_O_G_Cousin->edges[L"爸爸"] = M_B_Uncle;
        M_B_O_G_Cousin->edges[L"媽媽"] = M_B_Aunt;
        M_B_O_G_Cousin->edges[L"哥哥"] = M_B_O_B_Cousin;
        M_B_O_G_Cousin->edges[L"弟弟"] = M_B_Y__B_Cousin;
        M_B_O_G_Cousin->edges[L"姊姊"] = M_B_O_G_Cousin;
        M_B_O_G_Cousin->edges[L"妹妹"] = M_B_Y_G_Cousin;

        M_B_Y_G_Cousin->edges[L"爸爸"] = M_B_Uncle;
        M_B_Y_G_Cousin->edges[L"媽媽"] = M_B_Aunt;
        M_B_Y_G_Cousin->edges[L"哥哥"] = M_B_O_B_Cousin;
        M_B_Y_G_Cousin->edges[L"弟弟"] = M_B_Y__B_Cousin;
        M_B_Y_G_Cousin->edges[L"姊姊"] = M_B_O_G_Cousin;
        M_B_Y_G_Cousin->edges[L"妹妹"] = M_B_Y_G_Cousin;

        M_G_O_B_Cousin->edges[L"爸爸"] = MG_Uncle;
        M_G_O_B_Cousin->edges[L"媽媽"] = MG_Aunt;
        M_G_O_B_Cousin->edges[L"哥哥"] = M_G_O_B_Cousin;
        M_G_O_B_Cousin->edges[L"姊姊"] = M_G_O_G_Cousin;
        M_G_O_B_Cousin->edges[L"弟弟"] = M_G_Y_B_Cousin;
        M_G_O_B_Cousin->edges[L"妹妹"] = M_G_Y_G_Cousin;

        M_G_Y_B_Cousin->edges[L"爸爸"] = MG_Uncle;
        M_G_Y_B_Cousin->edges[L"媽媽"] = MG_Aunt;
        M_G_Y_B_Cousin->edges[L"哥哥"] = M_G_O_B_Cousin;
        M_G_Y_B_Cousin->edges[L"弟弟"] = M_G_Y_B_Cousin;
        M_G_Y_B_Cousin->edges[L"姊姊"] = M_G_O_G_Cousin;
        M_G_Y_B_Cousin->edges[L"妹妹"] = M_G_Y_G_Cousin;

        M_G_O_G_Cousin->edges[L"爸爸"] = MG_Uncle;
        M_G_O_G_Cousin->edges[L"媽媽"] = MG_Aunt;
        M_G_O_G_Cousin->edges[L"哥哥"] = M_G_O_B_Cousin;
        M_G_O_G_Cousin->edges[L"弟弟"] = M_G_Y_B_Cousin;
        M_G_O_G_Cousin->edges[L"姊姊"] = M_G_O_G_Cousin;
        M_G_O_G_Cousin->edges[L"妹妹"] = M_G_Y_G_Cousin;

        M_G_Y_G_Cousin->edges[L"爸爸"] = MG_Uncle;
        M_G_Y_G_Cousin->edges[L"媽媽"] = MG_Aunt;
        M_G_Y_G_Cousin->edges[L"哥哥"] = M_G_O_B_Cousin;
        M_G_Y_G_Cousin->edges[L"弟弟"] = M_G_Y_B_Cousin;
        M_G_Y_G_Cousin->edges[L"姊姊"] = M_G_O_G_Cousin;
        M_G_Y_G_Cousin->edges[L"妹妹"] = M_G_Y_G_Cousin;

        Husband_Father->edges[L"妻子"] = Husband_Mother;
        Husband_Father->edges[L"兒子(較年長)"] = Husband_O_Brother;
        Husband_Father->edges[L"兒子(較年輕)"] = Husband_Y_Brother;
        Husband_Father->edges[L"兒子"] = husband;
        Husband_Father->edges[L"女兒(較年長)"] = Husband_O_Sister;
        Husband_Father->edges[L"女兒(較年輕)"] = Husband_Y_Sister;

        Husband_Mother->edges[L"丈夫"] = Husband_Father;
        Husband_Mother->edges[L"兒子(較年長)"] = Husband_O_Brother;
        Husband_Mother->edges[L"兒子(較年輕)"] = Husband_Y_Brother;
        Husband_Mother->edges[L"兒子"] = husband;
        Husband_Mother->edges[L"女兒(較年長)"] = Husband_O_Sister;
        Husband_Mother->edges[L"女兒(較年輕)"] = Husband_Y_Sister;

        Husband_O_Sister_H->edges[L"妻子"] = Husband_O_Sister;
        Husband_O_Sister_H->edges[L"兒子(較年長)"] = Husband_O_Sister_Nephew;
        Husband_O_Sister_H->edges[L"兒子(較年輕)"] = Husband_O_Sister_Nephew;
        Husband_O_Sister_H->edges[L"兒子"] = Husband_O_Sister_Nephew;
        Husband_O_Sister_H->edges[L"女兒(較年長)"] = Husband_O_Sister_Concubine;
        Husband_O_Sister_H->edges[L"女兒(較年輕)"] = Husband_O_Sister_Concubine;
        Husband_O_Sister_H->edges[L"女兒"] = Husband_O_Sister_Concubine;

        Husband_O_Sister->edges[L"爸爸"] = Husband_Father;
        Husband_O_Sister->edges[L"媽媽"] = Husband_Mother;
        Husband_O_Sister->edges[L"哥哥"] = Husband_O_Brother;
        Husband_O_Sister->edges[L"弟弟"] = Husband_Y_Brother;
        Husband_O_Sister->edges[L"姊姊"] = Husband_O_Sister;
        Husband_O_Sister->edges[L"妹妹"] = Husband_Y_Sister;
        Husband_O_Sister->edges[L"丈夫"] = Husband_O_Sister_H;
        Husband_O_Sister->edges[L"兒子(較年長)"] = Husband_O_Sister_Nephew;
        Husband_O_Sister->edges[L"兒子(較年輕)"] = Husband_O_Sister_Nephew;
        Husband_O_Sister->edges[L"兒子"] = Husband_O_Sister_Nephew;
        Husband_O_Sister->edges[L"女兒(較年長)"] = Husband_O_Sister_Concubine;
        Husband_O_Sister->edges[L"女兒(較年輕)"] = Husband_O_Sister_Concubine;
        Husband_O_Sister->edges[L"女兒"] = Husband_O_Sister_Concubine;

        Husband_Y_Sister_H->edges[L"妻子"] = Husband_Y_Sister;
        Husband_Y_Sister_H->edges[L"兒子(較年長)"] = Husband_Y_Sister_Nephew;
        Husband_Y_Sister_H->edges[L"兒子(較年輕)"] = Husband_Y_Sister_Nephew;
        Husband_Y_Sister_H->edges[L"兒子"] = Husband_Y_Sister_Nephew;
        Husband_Y_Sister_H->edges[L"女兒(較年長)"] = Husband_Y_Sister_Concubine;
        Husband_Y_Sister_H->edges[L"女兒(較年輕)"] = Husband_Y_Sister_Concubine;
        Husband_Y_Sister_H->edges[L"女兒"] = Husband_Y_Sister_Concubine;

        Husband_Y_Sister->edges[L"爸爸"] = Husband_Father;
        Husband_Y_Sister->edges[L"媽媽"] = Husband_Mother;
        Husband_Y_Sister->edges[L"哥哥"] = Husband_O_Brother;
        Husband_Y_Sister->edges[L"弟弟"] = Husband_Y_Brother;
        Husband_Y_Sister->edges[L"姊姊"] = Husband_O_Sister;
        Husband_Y_Sister->edges[L"妹妹"] = Husband_Y_Sister;
        Husband_Y_Sister->edges[L"丈夫"] = Husband_Y_Sister_H;
        Husband_Y_Sister->edges[L"兒子(較年長)"] = Husband_Y_Sister_Nephew;
        Husband_Y_Sister->edges[L"兒子(較年輕)"] = Husband_Y_Sister_Nephew;
        Husband_Y_Sister->edges[L"兒子"] = Husband_Y_Sister_Nephew;
        Husband_Y_Sister->edges[L"女兒(較年長)"] = Husband_Y_Sister_Concubine;
        Husband_Y_Sister->edges[L"女兒(較年輕)"] = Husband_Y_Sister_Concubine;
        Husband_Y_Sister->edges[L"女兒"] = Husband_Y_Sister_Concubine;

        Husband_O_Sister_Nephew->edges[L"爸爸"] = Husband_O_Sister_H;
        Husband_O_Sister_Nephew->edges[L"媽媽"] = Husband_O_Sister;
        Husband_O_Sister_Nephew->edges[L"哥哥"] = Husband_O_Sister_Nephew;
        Husband_O_Sister_Nephew->edges[L"弟弟"] = Husband_O_Sister_Nephew;
        Husband_O_Sister_Nephew->edges[L"姊姊"] = Husband_O_Sister_Concubine;
        Husband_O_Sister_Nephew->edges[L"妹妹"] = Husband_O_Sister_Concubine;

        Husband_O_Sister_Concubine->edges[L"爸爸"] = Husband_O_Sister_H;
        Husband_O_Sister_Concubine->edges[L"媽媽"] = Husband_O_Sister;
        Husband_O_Sister_Concubine->edges[L"哥哥"] = Husband_O_Sister_Nephew;
        Husband_O_Sister_Concubine->edges[L"弟弟"] = Husband_O_Sister_Nephew;
        Husband_O_Sister_Concubine->edges[L"姊姊"] = Husband_O_Sister_Concubine;
        Husband_O_Sister_Concubine->edges[L"妹妹"] = Husband_O_Sister_Concubine;

        Husband_Y_Sister_Nephew->edges[L"爸爸"] = Husband_Y_Sister_H;
        Husband_Y_Sister_Nephew->edges[L"媽媽"] = Husband_Y_Sister;
        Husband_Y_Sister_Nephew->edges[L"哥哥"] = Husband_Y_Sister_Nephew;
        Husband_Y_Sister_Nephew->edges[L"弟弟"] = Husband_Y_Sister_Nephew;
        Husband_Y_Sister_Nephew->edges[L"姊姊"] = Husband_Y_Sister_Concubine;
        Husband_Y_Sister_Nephew->edges[L"妹妹"] = Husband_Y_Sister_Concubine;

        Husband_Y_Sister_Concubine->edges[L"爸爸"] = Husband_Y_Sister_H;
        Husband_Y_Sister_Concubine->edges[L"媽媽"] = Husband_Y_Sister;
        Husband_Y_Sister_Concubine->edges[L"哥哥"] = Husband_Y_Sister_Nephew;
        Husband_Y_Sister_Concubine->edges[L"弟弟"] = Husband_Y_Sister_Nephew;
        Husband_Y_Sister_Concubine->edges[L"姊姊"] = Husband_Y_Sister_Concubine;
        Husband_Y_Sister_Concubine->edges[L"妹妹"] = Husband_Y_Sister_Concubine;

        Husband_O_Brother_W->edges[L"丈夫"] = Husband_O_Brother;
        Husband_O_Brother_W->edges[L"兒子(較年長)"] = Husband_O_Brother_Nephew;
        Husband_O_Brother_W->edges[L"兒子(較年輕)"] = Husband_O_Brother_Nephew;
        Husband_O_Brother_W->edges[L"兒子"] = Husband_O_Brother_Nephew;
        Husband_O_Brother_W->edges[L"女兒(較年長)"] = Husband_O_Brother_Concubine;
        Husband_O_Brother_W->edges[L"女兒(較年輕)"] = Husband_O_Brother_Concubine;
        Husband_O_Brother_W->edges[L"女兒"] = Husband_O_Brother_Concubine;

        Husband_O_Brother->edges[L"爸爸"] = Husband_Father;
        Husband_O_Brother->edges[L"媽媽"] = Husband_Mother;
        Husband_O_Brother->edges[L"哥哥"] = Husband_O_Brother;
        Husband_O_Brother->edges[L"妹妹"] = Husband_Y_Sister;
        Husband_O_Brother->edges[L"弟弟"] = Husband_Y_Brother;
        Husband_O_Brother->edges[L"姊姊"] = Husband_O_Sister;
        Husband_O_Brother->edges[L"妻子"] = Husband_O_Brother_W;
        Husband_O_Brother->edges[L"兒子(較年長)"] = Husband_O_Brother_Nephew;
        Husband_O_Brother->edges[L"兒子(較年輕)"] = Husband_O_Brother_Nephew;
        Husband_O_Brother->edges[L"兒子"] = Husband_O_Brother_Nephew;
        Husband_O_Brother->edges[L"女兒(較年長)"] = Husband_O_Brother_Concubine;
        Husband_O_Brother->edges[L"女兒(較年輕)"] = Husband_O_Brother_Concubine;
        Husband_O_Brother->edges[L"女兒"] = Husband_O_Brother_Concubine;

        Husband_Y_Brother_W->edges[L"丈夫"] = Husband_Y_Brother;
        Husband_Y_Brother_W->edges[L"兒子(較年長)"] = Husband_Y_Brother_Nephew;
        Husband_Y_Brother_W->edges[L"兒子(較年輕)"] = Husband_Y_Brother_Nephew;
        Husband_Y_Brother_W->edges[L"兒子"] = Husband_Y_Brother_Nephew;
        Husband_Y_Brother_W->edges[L"女兒(較年長)"] = Husband_Y_Brother_Concubine;
        Husband_Y_Brother_W->edges[L"女兒(較年輕)"] = Husband_Y_Brother_Concubine;
        Husband_Y_Brother_W->edges[L"女兒"] = Husband_Y_Brother_Concubine;

        Husband_Y_Brother->edges[L"爸爸"] = Husband_Father;
        Husband_Y_Brother->edges[L"媽媽"] = Husband_Mother;
        Husband_Y_Brother->edges[L"妹妹"] = Husband_Y_Sister;
        Husband_Y_Brother->edges[L"哥哥"] = Husband_O_Brother;
        Husband_Y_Brother->edges[L"弟弟"] = Husband_Y_Brother;
        Husband_Y_Brother->edges[L"姊姊"] = Husband_O_Sister;
        Husband_Y_Brother->edges[L"妻子"] = Husband_Y_Brother_W;
        Husband_Y_Brother->edges[L"兒子(較年長)"] = Husband_Y_Brother_Nephew;
        Husband_Y_Brother->edges[L"兒子(較年輕)"] = Husband_Y_Brother_Nephew;
        Husband_Y_Brother->edges[L"兒子"] = Husband_Y_Brother_Nephew;
        Husband_Y_Brother->edges[L"女兒(較年長)"] = Husband_Y_Brother_Concubine;
        Husband_Y_Brother->edges[L"女兒(較年輕)"] = Husband_Y_Brother_Concubine;
        Husband_Y_Brother->edges[L"女兒"] = Husband_Y_Brother_Concubine;

        Husband_O_Brother_Nephew->edges[L"爸爸"] = Husband_O_Brother;
        Husband_O_Brother_Nephew->edges[L"媽媽"] = Husband_O_Brother_W;
        Husband_O_Brother_Nephew->edges[L"姊姊"] = Husband_O_Brother_Concubine;
        Husband_O_Brother_Nephew->edges[L"妹妹"] = Husband_O_Brother_Concubine;
        Husband_O_Brother_Nephew->edges[L"哥哥"] = Husband_O_Brother_Nephew;
        Husband_O_Brother_Nephew->edges[L"弟弟"] = Husband_O_Brother_Nephew;

        Husband_O_Brother_Concubine->edges[L"爸爸"] = Husband_O_Brother;
        Husband_O_Brother_Concubine->edges[L"媽媽"] = Husband_O_Brother_W;
        Husband_O_Brother_Concubine->edges[L"姊姊"] = Husband_O_Brother_Concubine;
        Husband_O_Brother_Concubine->edges[L"妹妹"] = Husband_O_Brother_Concubine;
        Husband_O_Brother_Concubine->edges[L"哥哥"] = Husband_O_Brother_Nephew;
        Husband_O_Brother_Concubine->edges[L"弟弟"] = Husband_O_Brother_Nephew;

        Husband_Y_Brother_Nephew->edges[L"爸爸"] = Husband_Y_Brother;
        Husband_Y_Brother_Nephew->edges[L"媽媽"] = Husband_Y_Brother_W;
        Husband_Y_Brother_Nephew->edges[L"姊姊"] = Husband_Y_Brother_Concubine;
        Husband_Y_Brother_Nephew->edges[L"妹妹"] = Husband_Y_Brother_Concubine;
        Husband_Y_Brother_Nephew->edges[L"哥哥"] = Husband_Y_Brother_Nephew;
        Husband_Y_Brother_Nephew->edges[L"弟弟"] = Husband_Y_Brother_Nephew;

        Husband_Y_Brother_Concubine->edges[L"爸爸"] = Husband_Y_Brother;
        Husband_Y_Brother_Concubine->edges[L"媽媽"] = Husband_Y_Brother_W;
        Husband_Y_Brother_Concubine->edges[L"姊姊"] = Husband_Y_Brother_Concubine;
        Husband_Y_Brother_Concubine->edges[L"妹妹"] = Husband_Y_Brother_Concubine;
        Husband_Y_Brother_Concubine->edges[L"哥哥"] = Husband_Y_Brother_Nephew;
        Husband_Y_Brother_Concubine->edges[L"弟弟"] = Husband_Y_Brother_Nephew;

        B_Son->edges[L"爸爸"] = MB;
        B_Son->edges[L"媽媽"] = wife;
        B_Son->edges[L"哥哥"] = B_Son;
        B_Son->edges[L"弟弟"] = B_Son;
        B_Son->edges[L"姊姊"] = B_Daughter;
        B_Son->edges[L"妹妹"] = B_Daughter;
        B_Son->edges[L"妻子"] = B_DIL;
        B_Son->edges[L"兒子(較年長)"] = B_Grandson;
        B_Son->edges[L"兒子(較年輕)"] = B_Grandson;
        B_Son->edges[L"兒子"] = B_Grandson;
        B_Son->edges[L"女兒(較年長)"] = B_GrandDau;
        B_Son->edges[L"女兒(較年輕)"] = B_GrandDau;
        B_Son->edges[L"女兒"] = B_GrandDau;

        G_Son->edges[L"爸爸"] = husband;
        G_Son->edges[L"媽媽"] = MG;
        G_Son->edges[L"哥哥"] = G_Son;
        G_Son->edges[L"弟弟"] = G_Son;
        G_Son->edges[L"姊姊"] = G_Daughter;
        G_Son->edges[L"妹妹"] = G_Daughter;
        G_Son->edges[L"妻子"] = G_DIL;
        G_Son->edges[L"兒子(較年長)"] = G_Grandson;
        G_Son->edges[L"兒子(較年輕)"] = G_Grandson;
        G_Son->edges[L"兒子"] = G_Grandson;
        G_Son->edges[L"女兒(較年長)"] = G_GrandDau;
        G_Son->edges[L"女兒(較年輕)"] = G_GrandDau;
        G_Son->edges[L"女兒"] = G_GrandDau;

        B_Daughter->edges[L"爸爸"] = MB;
        B_Daughter->edges[L"媽媽"] = wife;
        B_Daughter->edges[L"哥哥"] = B_Son;
        B_Daughter->edges[L"弟弟"] = B_Son;
        B_Daughter->edges[L"姊姊"] = B_Daughter;
        B_Daughter->edges[L"妹妹"] = B_Daughter;
        B_Daughter->edges[L"丈夫"] = B_SIL;
        B_Daughter->edges[L"兒子(較年長)"] = B_Dau_Grandson;
        B_Daughter->edges[L"兒子(較年輕)"] = B_Dau_Grandson;
        B_Daughter->edges[L"兒子"] = B_Dau_Grandson;
        B_Daughter->edges[L"女兒(較年長)"] = B_Dau_Grandson;
        B_Daughter->edges[L"女兒(較年輕)"] = B_Dau_Grandson;
        B_Daughter->edges[L"女兒"] = B_Dau_Grandson;

        G_Daughter->edges[L"爸爸"] = husband;
        G_Daughter->edges[L"媽媽"] = MG;
        G_Daughter->edges[L"哥哥"] = G_Son;
        G_Daughter->edges[L"弟弟"] = G_Son;
        G_Daughter->edges[L"姊姊"] = G_Daughter;
        G_Daughter->edges[L"妹妹"] = G_Daughter;
        G_Daughter->edges[L"丈夫"] = G_SIL;
        G_Daughter->edges[L"兒子(較年長)"] = G_Dau_Grandson;
        G_Daughter->edges[L"兒子(較年輕)"] = G_Dau_Grandson;
        G_Daughter->edges[L"兒子"] = G_Dau_Grandson;
        G_Daughter->edges[L"女兒(較年長)"] = G_Dau_Grandson;
        G_Daughter->edges[L"女兒(較年輕)"] = G_Dau_Grandson;
        G_Daughter->edges[L"女兒"] = G_Dau_Grandson;

        B_Grandson->edges[L"爸爸"] = B_Son;
        B_Grandson->edges[L"媽媽"] = B_DIL;
        B_Grandson->edges[L"哥哥"] = B_Grandson;
        B_Grandson->edges[L"弟弟"] = B_Grandson;
        B_Grandson->edges[L"姊姊"] = B_GrandDau;
        B_Grandson->edges[L"妹妹"] = B_GrandDau;

        B_GrandDau->edges[L"爸爸"] = B_Son;
        B_GrandDau->edges[L"媽媽"] = B_DIL;
        B_GrandDau->edges[L"哥哥"] = B_Grandson;
        B_GrandDau->edges[L"弟弟"] = B_Grandson;
        B_GrandDau->edges[L"姊姊"] = B_GrandDau;
        B_GrandDau->edges[L"妹妹"] = B_GrandDau;

        B_Dau_Grandson->edges[L"爸爸"] = B_SIL;
        B_Dau_Grandson->edges[L"媽媽"] = B_Daughter;
        B_Dau_Grandson->edges[L"哥哥"] = B_Dau_Grandson;
        B_Dau_Grandson->edges[L"弟弟"] = B_Dau_Grandson;
        B_Dau_Grandson->edges[L"姊姊"] = B_Dau_Grandson;
        B_Dau_Grandson->edges[L"妹妹"] = B_Dau_Grandson;

        G_Grandson->edges[L"爸爸"] = G_Son;
        G_Grandson->edges[L"媽媽"] = G_DIL;
        G_Grandson->edges[L"哥哥"] = G_Grandson;
        G_Grandson->edges[L"弟弟"] = G_Grandson;
        G_Grandson->edges[L"姊姊"] = G_GrandDau;
        G_Grandson->edges[L"妹妹"] = G_GrandDau;

        G_GrandDau->edges[L"爸爸"] = G_Son;
        G_GrandDau->edges[L"媽媽"] = G_DIL;
        G_GrandDau->edges[L"哥哥"] = G_Grandson;
        G_GrandDau->edges[L"弟弟"] = G_Grandson;
        G_GrandDau->edges[L"姊姊"] = G_GrandDau;
        G_GrandDau->edges[L"妹妹"] = G_GrandDau;

        G_Dau_Grandson->edges[L"爸爸"] = G_SIL;
        G_Dau_Grandson->edges[L"媽媽"] = G_Daughter;
        G_Dau_Grandson->edges[L"哥哥"] = G_Dau_Grandson;
        G_Dau_Grandson->edges[L"弟弟"] = G_Dau_Grandson;
        G_Dau_Grandson->edges[L"姊姊"] = G_Dau_Grandson;
        G_Dau_Grandson->edges[L"妹妹"] = G_Dau_Grandson;

        B_DIL->edges[L"丈夫"] = B_Son;
        B_DIL->edges[L"兒子(較年長)"] = B_Grandson;
        B_DIL->edges[L"兒子(較年輕)"] = B_Grandson;
        B_DIL->edges[L"兒子"] = B_Grandson;
        B_DIL->edges[L"女兒(較年長)"] = B_GrandDau;
        B_DIL->edges[L"女兒(較年輕)"] = B_GrandDau;
        B_DIL->edges[L"女兒"] = B_GrandDau;

        B_SIL->edges[L"妻子"] = B_Daughter;
        B_SIL->edges[L"兒子(較年長)"] = B_Dau_Grandson;
        B_SIL->edges[L"兒子(較年輕)"] = B_Dau_Grandson;
        B_SIL->edges[L"兒子"] = B_Dau_Grandson;
        B_SIL->edges[L"女兒(較年長)"] = B_Dau_Grandson;
        B_SIL->edges[L"女兒(較年輕)"] = B_Dau_Grandson;
        B_SIL->edges[L"女兒"] = B_Dau_Grandson;

        G_DIL->edges[L"丈夫"] = G_Son;
        G_DIL->edges[L"兒子(較年長)"] = G_Grandson;
        G_DIL->edges[L"兒子(較年輕)"] = G_Grandson;
        G_DIL->edges[L"兒子"] = G_Grandson;
        G_DIL->edges[L"女兒(較年長)"] = G_GrandDau;
        G_DIL->edges[L"女兒(較年輕)"] = G_GrandDau;
        G_DIL->edges[L"女兒"] = G_GrandDau;

        G_SIL->edges[L"妻子"] = G_Daughter;
        G_SIL->edges[L"兒子(較年長)"] = G_Dau_Grandson;
        G_SIL->edges[L"兒子(較年輕)"] = G_Dau_Grandson;
        G_SIL->edges[L"兒子"] = G_Dau_Grandson;
        G_SIL->edges[L"女兒(較年長)"] = G_Dau_Grandson;
        G_SIL->edges[L"女兒(較年輕)"] = G_Dau_Grandson;
        G_SIL->edges[L"女兒"] = G_Dau_Grandson;

        Wife_Father->edges[L"妻子"] = Wife_Mother;
        Wife_Father->edges[L"兒子(較年長)"] = Wife_O_Brother;
        Wife_Father->edges[L"兒子(較年輕)"] = Wife_Y_Brother;
        Wife_Father->edges[L"兒子"] = Wife_Y_Brother;
        Wife_Father->edges[L"女兒(較年長)"] = Wife_O_Sister;
        Wife_Father->edges[L"女兒(較年輕)"] = Wife_Y_Sister;
        Wife_Father->edges[L"女兒"] = wife;

        Wife_Mother->edges[L"丈夫"] = Wife_Father;
        Wife_Mother->edges[L"兒子(較年長)"] = Wife_O_Brother;
        Wife_Mother->edges[L"兒子(較年輕)"] = Wife_Y_Brother;
        Wife_Mother->edges[L"兒子"] = Wife_Y_Brother;
        Wife_Mother->edges[L"女兒(較年長)"] = Wife_O_Sister;
        Wife_Mother->edges[L"女兒(較年輕)"] = Wife_Y_Sister;
        Wife_Mother->edges[L"女兒"] = wife;

        Wife_O_Brother->edges[L"爸爸"] = Wife_Father;
        Wife_O_Brother->edges[L"媽媽"] = Wife_Mother;
        Wife_O_Brother->edges[L"妻子"] = Wife_O_Brother_W;
        Wife_O_Brother->edges[L"哥哥"] = Wife_O_Brother;
        Wife_O_Brother->edges[L"弟弟"] = Wife_Y_Brother;
        Wife_O_Brother->edges[L"姊姊"] = Wife_O_Sister;
        Wife_O_Brother->edges[L"妹妹"] = Wife_Y_Sister;
        Wife_O_Brother->edges[L"兒子(較年長)"] = Wife_B_Nephew;
        Wife_O_Brother->edges[L"兒子(較年輕)"] = Wife_B_Nephew;
        Wife_O_Brother->edges[L"兒子"] = Wife_B_Nephew;
        Wife_O_Brother->edges[L"女兒(較年長)"] = Wife_Bo_Concubine;
        Wife_O_Brother->edges[L"女兒(較年輕)"] = Wife_Bo_Concubine;
        Wife_O_Brother->edges[L"女兒"] = Wife_Bo_Concubine;

        Wife_O_Brother_W->edges[L"丈夫"] = Wife_O_Brother;
        Wife_O_Brother_W->edges[L"兒子(較年長)"] = Wife_B_Nephew;
        Wife_O_Brother_W->edges[L"兒子(較年輕)"] = Wife_B_Nephew;
        Wife_O_Brother_W->edges[L"兒子"] = Wife_B_Nephew;
        Wife_O_Brother_W->edges[L"女兒(較年長)"] = Wife_Bo_Concubine;
        Wife_O_Brother_W->edges[L"女兒(較年輕)"] = Wife_Bo_Concubine;
        Wife_O_Brother_W->edges[L"女兒"] = Wife_Bo_Concubine;

        Wife_Y_Brother->edges[L"爸爸"] = Wife_Father;
        Wife_Y_Brother->edges[L"媽媽"] = Wife_Mother;
        Wife_Y_Brother->edges[L"妻子"] = Wife_Y_Brother_W;
        Wife_Y_Brother->edges[L"哥哥"] = Wife_O_Brother;
        Wife_Y_Brother->edges[L"弟弟"] = Wife_Y_Brother;
        Wife_Y_Brother->edges[L"姊姊"] = Wife_O_Sister;
        Wife_Y_Brother->edges[L"妹妹"] = Wife_Y_Sister;
        Wife_Y_Brother->edges[L"兒子(較年長)"] = Wife_By_Nephew;
        Wife_Y_Brother->edges[L"兒子(較年輕)"] = Wife_By_Nephew;
        Wife_Y_Brother->edges[L"兒子"] = Wife_By_Nephew;
        Wife_Y_Brother->edges[L"女兒(較年長)"] = Wife_By_Concubine;
        Wife_Y_Brother->edges[L"女兒(較年輕)"] = Wife_By_Concubine;
        Wife_Y_Brother->edges[L"女兒"] = Wife_By_Concubine;

        Wife_Y_Brother_W->edges[L"丈夫"] = Wife_Y_Brother;
        Wife_Y_Brother_W->edges[L"兒子(較年長)"] = Wife_By_Nephew;
        Wife_Y_Brother_W->edges[L"兒子(較年輕)"] = Wife_By_Nephew;
        Wife_Y_Brother_W->edges[L"兒子"] = Wife_By_Nephew;
        Wife_Y_Brother_W->edges[L"女兒(較年長)"] = Wife_By_Concubine;
        Wife_Y_Brother_W->edges[L"女兒(較年輕)"] = Wife_By_Concubine;
        Wife_Y_Brother_W->edges[L"女兒"] = Wife_By_Concubine;

        Wife_O_Sister->edges[L"爸爸"] = Wife_Father;
        Wife_O_Sister->edges[L"媽媽"] = Wife_Mother;
        Wife_O_Sister->edges[L"丈夫"] = Wife_O_Sister_H;
        Wife_O_Sister->edges[L"哥哥"] = Wife_O_Brother;
        Wife_O_Sister->edges[L"弟弟"] = Wife_Y_Brother;
        Wife_O_Sister->edges[L"姊姊"] = Wife_O_Sister;
        Wife_O_Sister->edges[L"妹妹"] = Wife_Y_Sister;
        Wife_O_Sister->edges[L"兒子(較年長)"] = Wife_G_O_Nephew;
        Wife_O_Sister->edges[L"兒子(較年輕)"] = Wife_G_O_Nephew;
        Wife_O_Sister->edges[L"兒子"] = Wife_G_O_Nephew;
        Wife_O_Sister->edges[L"女兒(較年長)"] = Wife_G_O_Concubine;
        Wife_O_Sister->edges[L"女兒(較年輕)"] = Wife_G_O_Concubine;
        Wife_O_Sister->edges[L"女兒"] = Wife_G_O_Concubine;

        Wife_O_Sister_H->edges[L"妻子"] = Wife_O_Sister;
        Wife_O_Sister_H->edges[L"兒子(較年長)"] = Wife_G_O_Nephew;
        Wife_O_Sister_H->edges[L"兒子(較年輕)"] = Wife_G_O_Nephew;
        Wife_O_Sister_H->edges[L"兒子"] = Wife_G_O_Nephew;
        Wife_O_Sister_H->edges[L"女兒(較年長)"] = Wife_G_O_Concubine;
        Wife_O_Sister_H->edges[L"女兒(較年輕)"] = Wife_G_O_Concubine;
        Wife_O_Sister_H->edges[L"女兒"] = Wife_G_O_Concubine;

        Wife_Y_Sister->edges[L"爸爸"] = Wife_Father;
        Wife_Y_Sister->edges[L"媽媽"] = Wife_Mother;
        Wife_Y_Sister->edges[L"丈夫"] = Wife_Y_Sister_H;
        Wife_Y_Sister->edges[L"哥哥"] = Wife_O_Brother;
        Wife_Y_Sister->edges[L"弟弟"] = Wife_Y_Brother;
        Wife_Y_Sister->edges[L"姊姊"] = Wife_O_Sister;
        Wife_Y_Sister->edges[L"妹妹"] = Wife_Y_Sister;
        Wife_Y_Sister->edges[L"兒子(較年長)"] = Wife_G_Y_Nephew;
        Wife_Y_Sister->edges[L"兒子(較年輕)"] = Wife_G_Y_Nephew;
        Wife_Y_Sister->edges[L"兒子"] = Wife_G_Y_Nephew;
        Wife_Y_Sister->edges[L"女兒(較年長)"] = Wife_G_Y_Concubine;
        Wife_Y_Sister->edges[L"女兒(較年輕)"] = Wife_G_Y_Concubine;
        Wife_Y_Sister->edges[L"女兒"] = Wife_G_Y_Concubine;

        Wife_Y_Sister_H->edges[L"妻子"] = Wife_Y_Sister;
        Wife_Y_Sister_H->edges[L"兒子(較年長)"] = Wife_G_Y_Nephew;
        Wife_Y_Sister_H->edges[L"兒子(較年輕)"] = Wife_G_Y_Nephew;
        Wife_Y_Sister_H->edges[L"兒子"] = Wife_G_Y_Nephew;
        Wife_Y_Sister_H->edges[L"女兒(較年長)"] = Wife_G_Y_Concubine;
        Wife_Y_Sister_H->edges[L"女兒(較年輕)"] = Wife_G_Y_Concubine;
        Wife_Y_Sister_H->edges[L"女兒"] = Wife_G_Y_Concubine;

        Wife_B_Nephew->edges[L"爸爸"] = Wife_O_Brother;
        Wife_B_Nephew->edges[L"媽媽"] = Wife_O_Brother_W;
        Wife_B_Nephew->edges[L"哥哥"] = Wife_B_Nephew;
        Wife_B_Nephew->edges[L"弟弟"] = Wife_B_Nephew;
        Wife_B_Nephew->edges[L"姊姊"] = Wife_Bo_Concubine;
        Wife_B_Nephew->edges[L"妹妹"] = Wife_Bo_Concubine;

        Wife_Bo_Concubine->edges[L"爸爸"] = Wife_O_Brother;
        Wife_Bo_Concubine->edges[L"媽媽"] = Wife_O_Brother_W;
        Wife_Bo_Concubine->edges[L"哥哥"] = Wife_B_Nephew;
        Wife_Bo_Concubine->edges[L"弟弟"] = Wife_B_Nephew;
        Wife_Bo_Concubine->edges[L"姊姊"] = Wife_Bo_Concubine;
        Wife_Bo_Concubine->edges[L"妹妹"] = Wife_Bo_Concubine;

        Wife_By_Nephew->edges[L"爸爸"] = Wife_Y_Brother;
        Wife_By_Nephew->edges[L"媽媽"] = Wife_Y_Brother_W;
        Wife_By_Nephew->edges[L"哥哥"] = Wife_By_Nephew;
        Wife_By_Nephew->edges[L"弟弟"] = Wife_By_Nephew;
        Wife_By_Nephew->edges[L"姊姊"] = Wife_By_Concubine;
        Wife_By_Nephew->edges[L"妹妹"] = Wife_By_Concubine;

        Wife_By_Concubine->edges[L"爸爸"] = Wife_Y_Brother;
        Wife_By_Concubine->edges[L"媽媽"] = Wife_Y_Brother_W;
        Wife_By_Concubine->edges[L"哥哥"] = Wife_By_Nephew;
        Wife_By_Concubine->edges[L"弟弟"] = Wife_By_Nephew;
        Wife_By_Concubine->edges[L"姊姊"] = Wife_By_Concubine;
        Wife_By_Concubine->edges[L"妹妹"] = Wife_By_Concubine;

        Wife_G_O_Nephew->edges[L"爸爸"] = Wife_O_Sister_H;
        Wife_G_O_Nephew->edges[L"媽媽"] = Wife_O_Sister;
        Wife_G_O_Nephew->edges[L"哥哥"] = Wife_G_O_Nephew;
        Wife_G_O_Nephew->edges[L"弟弟"] = Wife_G_O_Nephew;
        Wife_G_O_Nephew->edges[L"姊姊"] = Wife_G_O_Concubine;
        Wife_G_O_Nephew->edges[L"妹妹"] = Wife_G_O_Concubine;

        Wife_G_O_Concubine->edges[L"爸爸"] = Wife_O_Sister_H;
        Wife_G_O_Concubine->edges[L"媽媽"] = Wife_O_Sister;
        Wife_G_O_Concubine->edges[L"哥哥"] = Wife_G_O_Nephew;
        Wife_G_O_Concubine->edges[L"弟弟"] = Wife_G_O_Nephew;
        Wife_G_O_Concubine->edges[L"姊姊"] = Wife_G_O_Concubine;
        Wife_G_O_Concubine->edges[L"妹妹"] = Wife_G_O_Concubine;

        Wife_G_Y_Nephew->edges[L"爸爸"] = Wife_Y_Sister_H;
        Wife_G_Y_Nephew->edges[L"媽媽"] = Wife_Y_Sister;
        Wife_G_Y_Nephew->edges[L"哥哥"] = Wife_G_Y_Nephew;
        Wife_G_Y_Nephew->edges[L"弟弟"] = Wife_G_Y_Nephew;
        Wife_G_Y_Nephew->edges[L"姊姊"] = Wife_G_Y_Concubine;
        Wife_G_Y_Nephew->edges[L"妹妹"] = Wife_G_Y_Concubine;

        Wife_G_Y_Concubine->edges[L"爸爸"] = Wife_Y_Sister_H;
        Wife_G_Y_Concubine->edges[L"媽媽"] = Wife_Y_Sister;
        Wife_G_Y_Concubine->edges[L"哥哥"] = Wife_G_Y_Nephew;
        Wife_G_Y_Concubine->edges[L"弟弟"] = Wife_G_Y_Nephew;
        Wife_G_Y_Concubine->edges[L"姊姊"] = Wife_G_Y_Concubine;
        Wife_G_Y_Concubine->edges[L"妹妹"] = Wife_G_Y_Concubine;
    }

    void readFile(char* file)
    {
        search.clear();

        string str;
        ifstream inFile(file);
        wstring_convert<codecvt_utf8_utf16<wchar_t>> cvt;

        while (getline(inFile, str)) search.push_back(cvt.from_bytes(str));
    }

    vector<wstring> split(wstring ws)
    {
        vector<wstring> v;
        wstringstream wss(ws);
        while (getline(wss, ws, L'的')) v.push_back(ws);
        return v;
    }

    void print(shared_ptr<node> n, vector<wstring>& v, int i)
    {
        if (i == v.size()) { cout << n->name << '\n'; return; }
        print(n->edges[v[i]], v, i + 1);
    }

    void execute()
    {
        for (auto& ws : search)
        {
            auto v = split(ws);
            print(root, v, 0);
        }
    }

private:
    vector<wstring> search;

    // nodes
    shared_ptr<node> root;
    shared_ptr<node> MB;
    shared_ptr<node> MG;
    shared_ptr<node> father;
    shared_ptr<node> mother;
    shared_ptr<node> wife;
    shared_ptr<node> husband;

    shared_ptr<node> OlderBrother;
    shared_ptr<node> YoungerBrother;
    shared_ptr<node> OlderSister;
    shared_ptr<node> YoungerSister;

    shared_ptr<node> B_Son;
    shared_ptr<node> B_Daughter;
    shared_ptr<node> G_Son;
    shared_ptr<node> G_Daughter;
    shared_ptr<node> B_DIL;
    shared_ptr<node> B_SIL;
    shared_ptr<node> G_DIL;
    shared_ptr<node> G_SIL;
    shared_ptr<node> B_Grandson;
    shared_ptr<node> B_GrandDau;
    shared_ptr<node> G_Grandson;
    shared_ptr<node> G_GrandDau;
    shared_ptr<node> B_Dau_Grandson;
    shared_ptr<node> G_Dau_Grandson;

    shared_ptr<node> O_SIL;
    shared_ptr<node> Y_SIL;
    shared_ptr<node> O_BIL;
    shared_ptr<node> Y_BIL;
    shared_ptr<node> O_B_Nephew;
    shared_ptr<node> O_B_Concubine;
    shared_ptr<node> Y_B_Nephew;
    shared_ptr<node> Y_B_Concubine;
    shared_ptr<node> O_Sis_Nephew;
    shared_ptr<node> O_Sis_Concubine;
    shared_ptr<node> Y_Sis_Nephew;
    shared_ptr<node> Y_Sis_Concubine;

    shared_ptr<node> F_B_Uncle;
    shared_ptr<node> F_B_Y_Uncle;
    shared_ptr<node> F_B_O_Aunt;
    shared_ptr<node> F_B_Y_Aunt;
    shared_ptr<node> F_O_B_O_B_Cousin;
    shared_ptr<node> F_O_B_Y_B_Cousin;
    shared_ptr<node> F_O_B_O_G_Cousin;
    shared_ptr<node> F_O_B_Y_G_Cousin;
    shared_ptr<node> F_Y_B_O_B_Cousin;
    shared_ptr<node> F_Y_B_Y_B_Cousin;
    shared_ptr<node> F_Y_B_O_G_Cousin;
    shared_ptr<node> F_Y_B_Y_G_Cousin;

    shared_ptr<node> FG_Uncle;
    shared_ptr<node> FG_Aunt;
    shared_ptr<node> F_G_O_B_Cousin;
    shared_ptr<node> F_G_Y_B_Cousin;
    shared_ptr<node> F_G_O_G_Cousin;
    shared_ptr<node> F_G_Y_G_Cousin;

    shared_ptr<node> F_GrandFather;
    shared_ptr<node> F_GrandMother;
    shared_ptr<node> M_GrandFather;
    shared_ptr<node> M_GrandMother;

    shared_ptr<node> M_B_Uncle;
    shared_ptr<node> M_B_Aunt;
    shared_ptr<node> M_B_O_B_Cousin;
    shared_ptr<node> M_B_Y__B_Cousin;
    shared_ptr<node> M_B_O_G_Cousin;
    shared_ptr<node> M_B_Y_G_Cousin;

    shared_ptr<node> MG_Uncle;
    shared_ptr<node> MG_Aunt;
    shared_ptr<node> M_G_O_B_Cousin;
    shared_ptr<node> M_G_Y_B_Cousin;
    shared_ptr<node> M_G_O_G_Cousin;
    shared_ptr<node> M_G_Y_G_Cousin;

    shared_ptr<node> Husband_Father;
    shared_ptr<node> Husband_Mother;

    shared_ptr<node> Husband_O_Brother;
    shared_ptr<node> Husband_O_Brother_W;
    shared_ptr<node> Husband_Y_Brother;
    shared_ptr<node> Husband_Y_Brother_W;
    shared_ptr<node> Husband_O_Brother_Nephew;
    shared_ptr<node> Husband_O_Brother_Concubine;
    shared_ptr<node> Husband_Y_Brother_Nephew;
    shared_ptr<node> Husband_Y_Brother_Concubine;

    shared_ptr<node> Husband_O_Sister;
    shared_ptr<node> Husband_O_Sister_H;
    shared_ptr<node> Husband_Y_Sister;
    shared_ptr<node> Husband_Y_Sister_H;
    shared_ptr<node> Husband_O_Sister_Nephew;
    shared_ptr<node> Husband_O_Sister_Concubine;
    shared_ptr<node> Husband_Y_Sister_Nephew;
    shared_ptr<node> Husband_Y_Sister_Concubine;

    shared_ptr<node> Wife_Father;
    shared_ptr<node> Wife_Mother;

    shared_ptr<node> Wife_O_Brother;
    shared_ptr<node> Wife_O_Brother_W;
    shared_ptr<node> Wife_Y_Brother;
    shared_ptr<node> Wife_Y_Brother_W;

    shared_ptr<node> Wife_O_Sister;
    shared_ptr<node> Wife_O_Sister_H;
    shared_ptr<node> Wife_Y_Sister;
    shared_ptr<node> Wife_Y_Sister_H;
    shared_ptr<node> Wife_B_Nephew;
    shared_ptr<node> Wife_Bo_Concubine;
    shared_ptr<node> Wife_By_Nephew;
    shared_ptr<node> Wife_By_Concubine;
    shared_ptr<node> Wife_G_O_Nephew;
    shared_ptr<node> Wife_G_O_Concubine;
    shared_ptr<node> Wife_G_Y_Nephew;
    shared_ptr<node> Wife_G_Y_Concubine;
};

int main(int argc, char* argv[])
{
    Solution s;
    s.readFile(argv[1]);
    s.execute();
}