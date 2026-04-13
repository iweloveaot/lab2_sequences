// main.cpp - Консольный интерфейс для работы с последовательностями
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "tests.h"
#include "bit_sequence.h"
#include "mutable_array_sequence.h"
#include "immutable_array_sequence.h"
#include "mutable_list_sequence.h"
#include "immutable_list_sequence.h"
#include "array_sequence_builder.h"
#include "list_sequence_builder.h"

// ==================== Поддержка выбора типа элементов ====================

enum class ElementType { Int, String };

ElementType readElementType() {
    std::cout << "\nSelect element type:\n";
    std::cout << "1. int\n";
    std::cout << "2. string\n";
    std::cout << "Choice: ";
    
    int choice;
    while (!(std::cin >> choice) || choice < 1 || choice > 2) {
        std::cout << "Invalid input. Please enter 1 or 2: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cin.ignore(10000, '\n');
    return (choice == 1) ? ElementType::Int : ElementType::String;
}

template<typename T>
std::vector<T> parseElements(const std::string& input) {
    std::vector<T> result;
    std::stringstream ss(input);
    T item;
    while (ss >> item) {
        result.push_back(item);
    }
    return result;
}

template<typename T>
void printSequence(const Sequence<T>* seq, const std::string& label = "") {
    if (!label.empty()) std::cout << label << ": ";
    std::cout << "[";
    for (int i = 0; i < seq->GetLength(); ++i) {
        std::cout << seq->Get(i);
        if (i < seq->GetLength() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}

// ==================== Меню операций ====================

void showMainMenu() {
    std::cout << "\n=== WORKING WITH SEQUENCES UI ===\n";
    std::cout << "1. ArraySequence (Mutable)\n";
    std::cout << "2. ArraySequence (Immutable)\n";
    std::cout << "3. ListSequence (Mutable)\n";
    std::cout << "4. ListSequence (Immutable)\n";
    std::cout << "5. BitSequence\n";
    std::cout << "6. Builders\n";
    std::cout << "7. Run Tests\n";
    std::cout << "0. Exit\n";
    std::cout << "Choice: ";
}

void showSequenceMenu(const std::string& typeName) {
    std::cout << "\n--- " << typeName << " Operations ---\n";
    std::cout << "1. Create from array\n";
    std::cout << "2. Append element\n";
    std::cout << "3. Prepend element\n";
    std::cout << "4. Insert at index\n";
    std::cout << "5. Get element by index\n";
    std::cout << "6. Get subsequence\n";
    std::cout << "7. Concatenate sequences\n";
    std::cout << "8. Map operation\n";
    std::cout << "9. Where (filter) operation\n";
    std::cout << "10. Reduce operation\n";
    std::cout << "11. TryGetFirst / TryGetLast\n";
    std::cout << "12. Iterate with enumerator\n";
    std::cout << "0. Back to main menu\n";
    std::cout << "Choice: ";
}

void showBitSequenceMenu() {
    std::cout << "\n--- BitSequence Operations ---\n";
    std::cout << "1. Create from bool array\n";
    std::cout << "2. Bitwise NOT (~)\n";
    std::cout << "3. Bitwise AND (&)\n";
    std::cout << "4. Bitwise OR (|)\n";
    std::cout << "5. Bitwise XOR (^)\n";
    std::cout << "6. GetSubsequence\n";
    std::cout << "0. Back to main menu\n";
    std::cout << "Choice: ";
}

template<typename SeqType, typename T>
SeqType* createSequenceFromArray() {
    std::cout << "Enter elements (space-separated): ";
    std::string input;
    std::getline(std::cin, input);
    if (input.empty()) 
        std::getline(std::cin, input);
    
    std::vector<T> elems = parseElements<T>(input);
    if (elems.empty()) {
        return new SeqType();
    }
    return new SeqType(elems.data(), static_cast<int>(elems.size()));
}

template<typename SeqType, typename T>
void interactiveSequenceDemo(const std::string& typeName) {
    SeqType* seq = nullptr;
    SeqType* seq2 = nullptr;
    
    int choice;
    do {
        showSequenceMenu(typeName);
        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter command 0 to 12: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        std::cin.ignore(10000, '\n');
        
        try {
            switch (choice) {
                case 1: {
                    delete seq;
                    seq = createSequenceFromArray<SeqType, T>();
                    printSequence(seq, "Created");
                    break;
                }
                case 2: {
                    if (!seq) { 
                        std::cout << "Create sequence first!\n"; 
                        break; 
                    }
                    std::cout << "Enter value: ";
                    T val; 
                    std::cin >> val;
                    if constexpr (std::is_same<SeqType, ImmutableArraySequence<T>>::value ||
                                  std::is_same<SeqType, ImmutableListSequence<T>>::value) {
                        auto* newSeq = seq->Append(val);
                        printSequence(newSeq, "New sequence");
                        delete newSeq;
                    } else {
                        seq->Append(val);
                        printSequence(seq, "Updated");
                    }
                    break;
                }
                case 3: {
                    if (!seq) { 
                        std::cout << "Create sequence first!\n"; 
                        break; 
                    }
                    std::cout << "Enter value: ";
                    T val; 
                    std::cin >> val;
                    if constexpr (std::is_same<SeqType, ImmutableArraySequence<T>>::value ||
                                  std::is_same<SeqType, ImmutableListSequence<T>>::value) {
                        auto* newSeq = seq->Prepend(val);
                        printSequence(newSeq, "New sequence");
                        delete newSeq;
                    } else {
                        seq->Prepend(val);
                        printSequence(seq, "Updated");
                    }
                    break;
                }
                case 4: {
                    if (!seq) { 
                        std::cout << "Create sequence first!\n"; 
                        break; 
                    }
                    std::cout << "Enter index and value: ";
                    int idx;
                    T val; 
                    std::cin >> idx >> val;
                    if constexpr (std::is_same<SeqType, ImmutableArraySequence<T>>::value ||
                                  std::is_same<SeqType, ImmutableListSequence<T>>::value) {
                        auto* newSeq = seq->InsertAt(val, idx);
                        printSequence(newSeq, "New sequence");
                        delete newSeq;
                    } else {
                        seq->InsertAt(val, idx);
                        printSequence(seq, "Updated");
                    }
                    break;
                }
                case 5: {
                    if (!seq) { 
                        std::cout << "Create sequence first!\n"; 
                        break; 
                    }
                    std::cout << "Enter index: ";
                    int idx; 
                    std::cin >> idx;
                    std::cout << "Element: " << seq->Get(idx) << "\n";
                    break;
                }
                case 6: {
                    if (!seq) { 
                        std::cout << "Create sequence first!\n"; 
                        break; 
                    }
                    std::cout << "Enter start and end index: ";
                    int start, end; 
                    std::cin >> start >> end;
                    auto* sub = seq->GetSubsequence(start, end);
                    printSequence(sub, "Subsequence");
                    delete sub;
                    break;
                }
                case 7: {
                    if (!seq) { 
                        std::cout << "Create first sequence!\n"; 
                        break; 
                    }
                    std::cout << "Create second sequence:\n";
                    seq2 = createSequenceFromArray<SeqType, T>();
                    if constexpr (std::is_same<SeqType, ImmutableArraySequence<T>>::value ||
                                  std::is_same<SeqType, ImmutableListSequence<T>>::value) {
                        auto* result = seq->Concat(seq2);
                        printSequence(result, "Concatenated");
                        delete result;
                    } else {
                        seq->Concat(seq2);
                        printSequence(seq, "Concatenated");
                    }
                    delete seq2;
                    seq2 = nullptr;
                    break;
                }
                case 8: {
                    if (!seq) { 
                        std::cout << "Create sequence first!\n"; 
                        break; 
                    }
                    std::cout << "Map: x -> x * 2\n";
                    auto* mapped = seq->Map([](const T& x) {
                        if constexpr (std::is_same_v<T, int>) return x * 2;
                        else return std::string("[MAPPED] ") + x;
                    });
                    printSequence(mapped, "Mapped");
                    delete mapped;
                    break;
                }
                case 9: {
                    if (!seq) { 
                        std::cout << "Create sequence first!\n"; 
                        break; 
                    }
                    if constexpr (std::is_same_v<T, int>)
                        std::cout << "Filter: x > 0 (even numbers)\n";
                    else
                        std::cout << "Filter: length > 3\n";
                    auto* filtered = seq->Where([](const T& x) { 
                        if constexpr (std::is_same_v<T, int>) return x % 2 == 0;
                        else return x.length() > 3;
                    });
                    printSequence(filtered, "Filtered");
                    delete filtered;
                    break;
                }
                case 10: {
                    if (!seq) { 
                        std::cout << "Create sequence first!\n"; 
                        break; 
                    }
                    T result{};
                    seq->Reduce([](const T& a, const T& b) { 
                        if constexpr (std::is_same_v<T, int>) return a + b;
                        else return a + b;  // для string конкатенация
                    }, result, &result);
                    std::cout << "Added: " << result << "\n";
                    break;
                }
                case 11: {
                    if (!seq) { 
                        std::cout << "Create sequence first!\n"; 
                        break; 
                    }

                    auto first = seq->TryGetFirst([](const T& x) {
                        if constexpr (std::is_same_v<T, int>) return x > 5;
                        else return !x.empty();
                    });

                    if constexpr (std::is_same_v<T, int>) {
                        if (first.HasValue()) 
                            std::cout << "First > 5: " << first.GetValue() << "\n";
                        else 
                            std::cout << "No element > 5 found\n";
                    } else {
                        if (first.HasValue()) 
                            std::cout << "First not empty: " << first.GetValue() << "\n";
                        else 
                            std::cout << "No not empty element found\n";
                    }


                    auto last = seq->TryGetLast([](const T& x) {
                        if constexpr (std::is_same_v<T, int>) return x % 2 == 0;
                        else return x.length() > 2;
                    });

                    if constexpr (std::is_same_v<T, int>) {
                        if (last.HasValue()) 
                            std::cout << "Last even: " << last.GetValue() << "\n";
                        else 
                            std::cout << "No even element found\n";
                    } else {
                        if (last.HasValue()) 
                            std::cout << "Last with length > 2: " << last.GetValue() << "\n";
                        else 
                            std::cout << "No element with length > 2 found\n";
                    }
                    
                    break;
                }
                case 12: {
                    if (!seq) { 
                        std::cout << "Create sequence first!\n"; 
                        break; 
                    }
                    std::cout << "Iterating: ";
                    auto* iter = seq->GetEnumerator();
                    while (iter->HasNext()) {
                        std::cout << iter->GetCurrent() << " ";
                    }
                    std::cout << "\n";
                    delete iter;
                    break;
                }
                case 0:
                    break;
                default:
                    std::cout << "Invalid choice!\n";
            }
        } catch (const BaseException& e) {
            std::cout << "Error: " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    } while (choice != 0);
    
    delete seq;
    delete seq2;
}

std::vector<int> createBitArray() {
    std::cout << "Enter bits (0 or 1, space-separated): ";
    std::string input;
    std::getline(std::cin, input);
    if (input.empty()) 
        std::getline(std::cin, input);
                    
    std::vector<int> bits = parseElements<int>(input);
    return bits;
}

void bitSequenceDemo() {
    BitSequence* seq = nullptr;
    BitSequence* seq2 = nullptr;
    
    int choice;
    do {
        showBitSequenceMenu();
        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter command 0 to 6: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        std::cin.ignore(10000, '\n');
        
        try {
            switch (choice) {
                case 1: {
                    std::vector<int> bits = createBitArray();
                    delete seq;
                    seq = new BitSequence(bits.data(), static_cast<int>(bits.size()));
                    printSequence(seq, "Created");
                    break;
                }
                case 2: {
                    if (!seq) { 
                        std::cout << "Create sequence first!\n"; 
                        break; 
                    }
                    auto* result = ~(*seq);
                    printSequence(result, "NOT");
                    delete result;
                    break;
                }
                case 3: {
                    if (!seq) { 
                        std::cout << "Create sequence first!\n"; 
                        break; 
                    } 

                    delete seq2;
                    std::cout << "Create second sequence:\n";
                    std::vector<int> bits = createBitArray();
                    seq2 = new BitSequence(bits.data(), static_cast<int>(bits.size()));
                    
                    auto* result = (*seq) & (*seq2);
                    printSequence(result, "AND");
                    delete result;
                    break;
                }
                case 4: {
                    if (!seq) { 
                        std::cout << "Create sequence first!\n"; 
                        break; 
                    } 

                    delete seq2;
                    std::cout << "Create second sequence:\n";
                    std::vector<int> bits = createBitArray();
                    seq2 = new BitSequence(bits.data(), static_cast<int>(bits.size()));

                    auto* result = (*seq) | (*seq2);
                    printSequence(result, "OR");
                    delete result;
                    break;
                }
                case 5: {
                    if (!seq) { 
                        std::cout << "Create sequence first!\n"; 
                        break; 
                    } 
                    
                    delete seq2;
                    std::cout << "Create second sequence:\n";
                    std::vector<int> bits = createBitArray();
                    seq2 = new BitSequence(bits.data(), static_cast<int>(bits.size()));

                    auto* result = (*seq) ^ (*seq2);
                    printSequence(result, "XOR");
                    delete result;
                    break;
                }
                case 6: {
                    if (!seq) { 
                        std::cout << "Create sequence first!\n"; 
                        break; 
                    }
                    std::cout << "Enter start and end index: ";
                    int start, end; 
                    std::cin >> start >> end;
                    auto* sub = seq->GetSubsequence(start, end);
                    printSequence(sub, "Subsequence");
                    delete sub;
                    break;
                }
                case 0:
                    break;
                default:
                    std::cout << "Invalid choice!\n";
            }
        } catch (const BaseException& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    } while (choice != 0);
    
    delete seq;
    delete seq2;
}

void buildersDemo() {
    std::cout << "\n--- Builders Demo ---\n";
    
    // ArraySequence Builder
    std::cout << "\nArraySequence Builder:\n";
    ArraySequenceBuilder<int> arrBuilder;
    arrBuilder.Add(1).Add(2).Add(3).AddRange(std::vector<int>{4, 5}.data(), 2);
    
    auto* mutableArr = arrBuilder.BuildMutable();
    printSequence(mutableArr, "Mutable");
    delete mutableArr;
    
    auto* immutableArr = arrBuilder.SetImmutable(true).Build();
    printSequence(immutableArr, "Immutable");
    delete immutableArr;
    
    // ListSequence Builder
    std::cout << "\nListSequence Builder:\n";
    ListSequenceBuilder<int> listBuilder;
    listBuilder.Add(10).AddToFront(5).AddRange(std::vector<int>{15, 20}.data(), 2);
    
    auto* mutableList = listBuilder.BuildMutable();
    printSequence(mutableList, "Mutable");
    delete mutableList;
    
    auto* immutableList = listBuilder.SetImmutable(true).Build();
    printSequence(immutableList, "Immutable");
    delete immutableList;
}


int main() {
    
    int choice;
    do {
        showMainMenu();
        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter command 0 to 7: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        std::cin.ignore(10000, '\n');
        
        try {
            switch (choice) {
                case 1: {
                    ElementType et = readElementType();
                    if (et == ElementType::Int)
                        interactiveSequenceDemo<MutableArraySequence<int>, int>("ArraySequence (Mutable) [int]");
                    else
                        interactiveSequenceDemo<MutableArraySequence<std::string>, std::string>("ArraySequence (Mutable) [string]");
                    break;
                }
                case 2: {
                    ElementType et = readElementType();
                    if (et == ElementType::Int)
                        interactiveSequenceDemo<ImmutableArraySequence<int>, int>("ArraySequence (Immutable) [int]");
                    else
                        interactiveSequenceDemo<ImmutableArraySequence<std::string>, std::string>("ArraySequence (Immutable) [string]");
                    break;
                }
                case 3: {
                    ElementType et = readElementType();
                    if (et == ElementType::Int)
                        interactiveSequenceDemo<MutableListSequence<int>, int>("ListSequence (Mutable) [int]");
                    else
                        interactiveSequenceDemo<MutableListSequence<std::string>, std::string>("ListSequence (Mutable) [string]");
                    break;
                }
                case 4: {
                    ElementType et = readElementType();
                    if (et == ElementType::Int)
                        interactiveSequenceDemo<ImmutableListSequence<int>, int>("ListSequence (Immutable) [int]");
                    else
                        interactiveSequenceDemo<ImmutableListSequence<std::string>, std::string>("ListSequence (Immutable) [string]");
                    break;
                }
                case 5:
                    bitSequenceDemo();
                    break;
                case 6:
                    buildersDemo();
                    break;
                case 7:
                    runAllTests();
                    break;
                case 0:
                    std::cout << "Bye-bye!\n";
                    break;
                default:
                    std::cout << "Invalid choice!\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Unhandled error: " << e.what() << "\n";
        }
    } while (choice != 0);
    
    return 0;
}

