#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>
#include <stdbool.h>
#include <stdio.h>

#define MENU_EXIT       1
#define REGISTER_SCREEN 2
#define UPDATE_SCREEN   3
#define BACK_TO_MENU    4
#define PUSH            5

/*Car data and necessary structs*/
typedef struct {
    char brand[30];
    char model[30];
    int fabYear;
    int modelYear;
    float price;
} Car;

// Node structure for a DLL.
typedef struct Node {
    Car data;
    // Pointer to the next Node.
    struct Node *next;
    // Pointer to the previous Node.
    struct Node *previous;
} Node;

/*DLL FUNCTIONS*/
void push(Node **head, Car data);
/*WINDOW GLOBAL VARIABLES*/
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND createCar, readCars, deleteCar, updateCar, exitRegister;
HWND brandLabel, brandInput, modelLabel, modelInput, fabYearLabel, fabYearInput,
    modelYearLabel, modelYearInput, priceLabel, priceInput, registerButton,
    backButton;

// Navigation
enum currentScreen { MENU, REGISTER, READ, UPDATE, DEL } Screen = 0;

// Screens
void MenuScreen(HWND parent, bool isVisible);
void RegisterScreen(HWND parent);
void CarUpdateScreen(HWND parent);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine,
                   int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Car Register";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND window =
        CreateWindowEx(0, CLASS_NAME, L"Car Register", WS_OVERLAPPEDWINDOW,
                       CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                       CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    if (!window) {
        return 0;
    }

    ShowWindow(window, nCmdShow);

    MSG msg = {};

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_COMMAND:
        switch (wParam) {
        case REGISTER_SCREEN:
            Screen = REGISTER;
            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;
        case UPDATE_SCREEN:
            Screen = UPDATE;
            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;
        case PUSH:
            Node *head = NULL;
            Car newCar;
            wchar_t price[30], fabyear[30], modelyear[30];
            GetWindowTextW(brandInput, (wchar_t) newCar.brand, 30);
            GetWindowTextW(modelInput, (wchar_t) newCar.model, 30);
            GetWindowTextW(priceInput, price, 30);
            GetWindowTextW(fabYearInput, fabyear, 30);
            GetWindowTextW(modelYearInput, modelyear, 30);
            newCar.fabYear = atoi(&fabyear);
            newCar.modelYear = atoi(&modelyear);
            newCar.price = atof(&price);
            printf("%s", newCar.brand);
            printf("%s", newCar.model);
            printf("%f", newCar.price);
            printf("%d", newCar.fabYear);
            printf("%d", newCar.modelYear);
            push(&head, newCar);
        case BACK_TO_MENU:
            Screen = MENU;
            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
            break;
        case MENU_EXIT:
            if (MessageBox(hwnd, L"Você quer mesmo deixar a aplicação?",
                           L"Car Register", MB_OKCANCEL) == IDOK) {
                DestroyWindow(hwnd);
            }
        }
        break;
    case WM_CLOSE:
        if (MessageBox(hwnd, L"Você quer mesmo deixar a aplicação?",
                       L"Car Register", MB_OKCANCEL) == IDOK) {
            DestroyWindow(hwnd);
        }
        break;
    case WM_PAINT:
        if (Screen == MENU) {
            printf("Menu");
            MenuScreen(hwnd, true);
        } else if (Screen = REGISTER) {
            RegisterScreen(hwnd);
        } else if (Screen = UPDATE) {
            CarUpdateScreen(hwnd);
        }
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        // All painting occurs here, between BeginPaint and EndPaint.
        FillRect(hdc, &ps.rcPaint, (HBRUSH) GRAY_BRUSH);
        EndPaint(hwnd, &ps);
        printf("painted");
        break;
    case WM_CREATE:
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void MenuScreen(HWND parent, bool isVisible) {
    DestroyWindow(brandLabel);
    DestroyWindow(brandInput);
    DestroyWindow(modelLabel);
    DestroyWindow(modelInput);
    DestroyWindow(fabYearLabel);
    DestroyWindow(fabYearInput);
    DestroyWindow(modelYearLabel);
    DestroyWindow(modelYearInput);
    DestroyWindow(priceLabel);
    DestroyWindow(priceInput);
    DestroyWindow(registerButton);
    DestroyWindow(backButton);
    createCar =
        CreateWindowW(L"BUTTON", L"Criar Carro", WS_VISIBLE | WS_CHILD, 120, 20,
                      150, 40, parent, (HMENU) REGISTER_SCREEN, NULL, NULL);
    readCars = CreateWindowW(L"BUTTON", L"Ver carros", WS_VISIBLE | WS_CHILD,
                             120, 70, 150, 40, parent, NULL, NULL, NULL);
    updateCar =
        CreateWindowW(L"BUTTON", L"Modificar Carro", WS_VISIBLE | WS_CHILD, 120,
                      120, 150, 40, parent, (HMENU) UPDATE_SCREEN, NULL, NULL);
    deleteCar =
        CreateWindowW(L"BUTTON", L"Excluir Carro", WS_VISIBLE | WS_CHILD, 120,
                      170, 150, 40, parent, NULL, NULL, NULL);
    exitRegister =
        CreateWindowW(L"BUTTON", L"Sair", WS_VISIBLE | WS_CHILD, 120, 220, 150,
                      40, parent, (HMENU) MENU_EXIT, NULL, NULL);
}

void RegisterScreen(HWND parent) {
    DestroyWindow(createCar);
    DestroyWindow(readCars);
    DestroyWindow(deleteCar);
    DestroyWindow(updateCar);
    DestroyWindow(exitRegister);
    brandLabel = CreateWindowW(L"STATIC", L"Criar Carro", WS_VISIBLE | WS_CHILD,
                               120, 20, 150, 40, parent, NULL, NULL, NULL);
    SetWindowText(brandLabel, L"Marca:");
    brandInput = CreateWindowW(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER,
                               120, 70, 220, 40, parent, NULL, NULL, NULL);
    modelLabel = CreateWindowW(L"STATIC", L"Criar Carro", WS_VISIBLE | WS_CHILD,
                               120, 120, 150, 40, parent, NULL, NULL, NULL);
    SetWindowText(modelLabel, L"Modelo:");
    modelInput = CreateWindowW(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER,
                               120, 170, 220, 40, parent, NULL, NULL, NULL);
    fabYearLabel =
        CreateWindowW(L"STATIC", L"Criar Carro", WS_VISIBLE | WS_CHILD, 120,
                      220, 150, 40, parent, NULL, NULL, NULL);
    SetWindowText(fabYearLabel, L"Ano de Fabricação:");
    fabYearInput =
        CreateWindowW(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 120,
                      270, 220, 40, parent, NULL, NULL, NULL);
    modelYearLabel =
        CreateWindowW(L"STATIC", L"Criar Carro", WS_VISIBLE | WS_CHILD, 120,
                      320, 170, 40, parent, NULL, NULL, NULL);
    SetWindowText(modelYearLabel, L"Ano do Modelo:");
    modelYearInput =
        CreateWindowW(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 120,
                      370, 220, 40, parent, NULL, NULL, NULL);
    priceLabel = CreateWindowW(L"STATIC", L"Criar Carro", WS_VISIBLE | WS_CHILD,
                               400, 20, 150, 40, parent, NULL, NULL, NULL);
    SetWindowText(priceLabel, L"Preço:");
    priceInput = CreateWindowW(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER,
                               400, 70, 220, 40, parent, NULL, NULL, NULL);
    registerButton =
        CreateWindowW(L"BUTTON", L"Registrar Carro", WS_VISIBLE | WS_CHILD, 400,
                      420, 220, 40, parent, (HMENU) PUSH, NULL, NULL);
    backButton =
        CreateWindowW(L"BUTTON", L"Voltar ao Menu", WS_VISIBLE | WS_CHILD, 120,
                      420, 220, 40, parent, (HMENU) BACK_TO_MENU, NULL, NULL);
}

void CarUpdateScreen(HWND parent) {
    brandLabel = CreateWindowW(L"STATIC", L"Criar Carro", WS_VISIBLE | WS_CHILD,
                               120, 20, 150, 40, parent, NULL, NULL, NULL);
    SetWindowText(brandLabel, L"Marca:");
    brandInput = CreateWindowW(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER,
                               120, 70, 220, 40, parent, NULL, NULL, NULL);
    modelLabel = CreateWindowW(L"STATIC", L"Criar Carro", WS_VISIBLE | WS_CHILD,
                               120, 120, 150, 40, parent, NULL, NULL, NULL);
    SetWindowText(modelLabel, L"Modelo:");
    modelInput = CreateWindowW(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER,
                               120, 170, 220, 40, parent, NULL, NULL, NULL);
    fabYearLabel =
        CreateWindowW(L"STATIC", L"Criar Carro", WS_VISIBLE | WS_CHILD, 120,
                      220, 150, 40, parent, NULL, NULL, NULL);
    SetWindowText(fabYearLabel, L"Ano de Fabricação:");
    fabYearInput =
        CreateWindowW(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 120,
                      270, 220, 40, parent, NULL, NULL, NULL);
    modelYearLabel =
        CreateWindowW(L"STATIC", L"Criar Carro", WS_VISIBLE | WS_CHILD, 120,
                      320, 170, 40, parent, NULL, NULL, NULL);
    SetWindowText(modelYearLabel, L"Ano do Modelo:");
    modelYearInput =
        CreateWindowW(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER, 120,
                      370, 220, 40, parent, NULL, NULL, NULL);
    priceLabel = CreateWindowW(L"STATIC", L"Criar Carro", WS_VISIBLE | WS_CHILD,
                               400, 20, 150, 40, parent, NULL, NULL, NULL);
    SetWindowText(priceLabel, L"Preço:");
    priceInput = CreateWindowW(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER,
                               400, 70, 220, 40, parent, NULL, NULL, NULL);
    CreateWindowW(L"BUTTON", L"Atualizar dados do Carro", WS_VISIBLE | WS_CHILD,
                  400, 420, 220, 40, parent, NULL, NULL, NULL);
    CreateWindowW(L"BUTTON", L"Voltar ao Menu", WS_VISIBLE | WS_CHILD, 120, 420,
                  220, 40, parent, (HMENU) BACK_TO_MENU, NULL, NULL);
}

void push(struct Node **head, Car data) {
    Node *newNode = malloc(sizeof(Node));

    newNode->data = data;
    newNode->next = (*head);
    newNode->previous = NULL;

    if ((*head)) {
        (*head)->previous = newNode;
    }

    // The head's now pointing to the new node.
    (*head) = newNode;
}