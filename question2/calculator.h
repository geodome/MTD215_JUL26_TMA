#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "formula.h"
#include "gridwindow.h"
#include "widgets.h"

class CalculatorApp {
    private:
    Formula* formula;
    GridWindow* window;
    TextDisplay* text;
    BackspaceButton* bkbtn;
    AllClearButton* acbtn;
    ModuloButton* modbtn;
    DivButton* divbtn;
    MultiButton* mulbtn;
    SubButton* subbtn;
    AddButton* addbtn;
    EvalButton* evalbtn;
    DigitButton* dgbtns[10];
    DecButton* decbtn;
    SignButton* signbtn;
    public:
    CalculatorApp() {
        formula = new Formula();
        window = new GridWindow(6,4);
        text = new TextDisplay();
        window->pack(text, 0,0,4,1);
        bkbtn  = new BackspaceButton(text, formula);
        window->pack(bkbtn, 1, 0, 1, 1);
        acbtn = new AllClearButton(text, formula);
        window->pack(acbtn, 1, 1, 1, 1);
        modbtn = new ModuloButton(text, formula);
        window->pack(modbtn, 1, 2, 1, 1);
        divbtn = new DivButton(text, formula);
        window->pack(divbtn, 1, 3, 1, 1);
        mulbtn = new MultiButton(text, formula);
        window->pack(mulbtn, 2, 3, 1, 1);
        subbtn = new SubButton(text, formula);
        window->pack(subbtn, 3, 3, 1, 1);
        addbtn = new AddButton(text, formula);
        window->pack(addbtn, 4, 3, 1, 1);
        evalbtn = new EvalButton(text, formula);
        window->pack(evalbtn, 5, 3, 1, 1);
        for(int i=0; i<3; i++) {
            dgbtns[7+i] = new DigitButton(7+i, text, formula);
            window->pack(dgbtns[7+i], 2, i, 1, 1);
            dgbtns[4+i] = new DigitButton(4+i, text, formula);
            window->pack(dgbtns[4+i], 3, i, 1, 1);
            dgbtns[1+i] = new DigitButton(1+i, text, formula);
            window->pack(dgbtns[1+i], 4, i, 1, 1);
        }
        dgbtns[0] = new DigitButton(0, text, formula);
        window->pack(dgbtns[0], 5, 1, 1, 1);
        decbtn = new DecButton(text, formula);
        window->pack(decbtn, 5, 2, 1, 1);
        signbtn = new SignButton(text, formula);
        window->pack(signbtn, 5, 0, 1, 1);
    }
    void mainloop() {
        window->mainloop();
    }
    ~CalculatorApp() {
        delete signbtn;
        delete decbtn;
        for(int i=0; i<10; i++) {
            delete dgbtns[i];
        }
        delete evalbtn;
        delete addbtn;
        delete subbtn;
        delete mulbtn;
        delete divbtn;
        delete modbtn;
        delete acbtn;
        delete text;
        delete formula;
        delete window;
    }
};

#endif