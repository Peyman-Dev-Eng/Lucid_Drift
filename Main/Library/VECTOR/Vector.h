#include <array>
#include <exception>
#include <stdexcept>
#include <iostream>
#include "EmptySnakeBodyDataStructError.h"
#include "NotFoundElementError.h"
#include "InvalidInputError.h"

template <typename type>
class Vector
{
private:
    type* Body;
    type* AuxiliaryBody;
    std::size_t ElementNumber;
    std::size_t capacity;

    void CopyBodyToAuxiliaryBodyWithoutThisIndex( int index ) {
        AuxiliaryBody = new type[capacity];
        bool FindIndex = false;
        for (std::size_t counter = 0; counter < ElementNumber; counter++) {
            if (counter == index and not FindIndex) {
                FindIndex = true;
                continue;
            }
            if (FindIndex) {
                AuxiliaryBody[counter - 1] = Body[counter];
            } else {
                AuxiliaryBody[counter] = Body[counter];
            }
        }
        return;
    }

    void ExportFromAuxiliaryBodyToBody() {
        Body = AuxiliaryBody;
        return;
    }

    void CopyBodyToAuxiliaryBody() {
        if (this->IsEmpty()) {
            return;
        }
        capacity *= 2;
        AuxiliaryBody = new type[capacity];
        for (std::size_t counter = 0; counter < ElementNumber; counter++) {
            AuxiliaryBody[counter] = Body[counter];
        }
    }

    bool IsFull() const {
        if (ElementNumber >= capacity) {
            return true;
        }
        return false;
    }
    bool IsEmpty() const {
        if (ElementNumber == 0) {
            return true;
        }
        return false;
    }
public:
    Vector() {
        ElementNumber = 0;
        capacity = 2;
        Body = new type[capacity];
        AuxiliaryBody = nullptr;
    }

    // Copy Constractor
    Vector( const Vector& other ) {
        this->ElementNumber = other.ElementNumber;
        this->capacity = other.capacity;
        this->Body = new type[capacity];
        for (std::size_t counter = 0; counter < ElementNumber; counter++) {
            this->Body[counter] = other.Body[counter];
        }
    }

    Vector( int SetCapacity ) {
        capacity = SetCapacity;
        Body = new type[capacity];
    }

    // Move Constractor
    Vector(Vector&& other)
    {
        Body = other.Body;
        AuxiliaryBody = other.AuxiliaryBody;
        ElementNumber = other.ElementNumber;
        capacity = other.capacity;

        other.Body = nullptr;
        other.AuxiliaryBody = nullptr;
        other.ElementNumber = 0;
        other.capacity = 0;
    }

    // Initialization
    Vector( std::initializer_list<type> list ) {
        ElementNumber = 0;
        capacity = 2;
        Body = new type[capacity];
        for (const auto& it : list) {
            if (this->IsFull()) {
                this->Resize();
            }
            Body[ElementNumber++] = it;
        }
    }
    type* begin() const {
        return Body;
    }

    type* end() const {
        return Body + ( ElementNumber );
    }

    void Resize() {
        this->CopyBodyToAuxiliaryBody();
        delete[] Body;
        this->ExportFromAuxiliaryBodyToBody();
    }
    void Reserve() {
        ElementNumber = 0;
        capacity = 2;
        Body = new type[capacity];
    }
    void Clear() {
        delete[] Body;
        Body = nullptr;
        AuxiliaryBody = nullptr;
        ElementNumber = 0;
        capacity = 2;
    }

    void Append( const type& element ) {
        if (this->IsEmpty()) {
            this->Reserve();
        }
        if (this->IsFull()) {
            this->Resize();
        }
        Body[ElementNumber++] = element;
        return;
    }

    void Pop( int index ) {
        try {
            if (index > ( ElementNumber - 1 ) or index < 0) {
                throw std::out_of_range( "Snake body index out of range" );
            }
            this->CopyBodyToAuxiliaryBodyWithoutThisIndex( index );
            delete[] Body;
            this->ExportFromAuxiliaryBodyToBody();
            --ElementNumber;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what();
            std::cout << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what();
            std::cout << std::endl;
        }
    }

    void Remove( type element ) {
        try {
            int FindResult = Find( element );
            if (FindResult == -1) {
                throw NotFoundElementError();
            }
            AuxiliaryBody = new type[capacity];
            bool FindIndex = false;
            for (int i = 0; i < ElementNumber; i++) {
                if (i == FindResult and not FindIndex) {
                    FindIndex = true;
                    continue;
                }
                if (FindIndex) {
                    AuxiliaryBody[i - 1] = Body[i];
                } else {
                    AuxiliaryBody[i] = Body[i];
                }
            }
            delete[] Body;
            Body = AuxiliaryBody;
            --ElementNumber;
        } catch (const NotFoundElementError& e) {
            if constexpr (std::is_class_v<type>) {
                std::cerr << "Error: " << e.what();
                std::cout << std::endl;
            } else {
                std::cerr << "Error: " << e.what() << ' ' << element;
                std::cout << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what();
            std::cout << std::endl;
        }
    }

    int Find( type element ) const {
        int counter = 0;
        try {
            if (std::is_class_v<type>) {
                throw InvalidInputError( "Input Invalid." );
            }
            for (type* it = this->begin(); it <= this->end(); ++it) {
                if (*it == element) {
                    return counter;
                }
                ++counter;
            }
            return -1;
        } catch (const InvalidInputError& e) {
            std::cerr << "Error: " << e.what();
            std::cout << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what();
            std::cout << std::endl;
        }
    }

    void Insert( int index, type element ) {
        try {
            if (index > ( ElementNumber - 1 ) or index < 0) {
                throw std::out_of_range( "Snake body index out of range" );
            }
            if (this->IsFull()) {
                this->Resize();
            }
            AuxiliaryBody = new type[capacity];
            std::size_t counter = 0;
            std::size_t IndexElement;
            for (counter; counter < index; counter++) {
                AuxiliaryBody[counter] = Body[counter];
            }
            IndexElement = counter;
            AuxiliaryBody[counter++] = element;
            for (; counter < ElementNumber + 1; counter++, IndexElement++) {
                AuxiliaryBody[counter] = Body[IndexElement];
            }
            delete[] Body;
            Body = AuxiliaryBody;
            ++ElementNumber;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what();
            std::cout << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what();
            std::cout << std::endl;
        }
    }

    void PopBack() {
        this->CopyBodyToAuxiliaryBodyWithoutThisIndex( ElementNumber - 1 );
        delete[] Body;
        this->ExportFromAuxiliaryBodyToBody();
        --ElementNumber;
    }

    void PushFront( type element ) {
        if (this->IsFull()) {
            capacity *= 2;
        }
        AuxiliaryBody = new type[capacity];
        AuxiliaryBody[0] = element;
        std::size_t index = 1;
        for (std::size_t counter = 0; counter < ElementNumber; counter++, index++) {
            AuxiliaryBody[index] = Body[counter];
        }
        delete[] Body;
        Body = AuxiliaryBody;
        ++ElementNumber;
    }

    std::size_t Capacity() const {
        return capacity;
    }

    std::size_t Size() const {
        return ElementNumber;
    }

    type& operator[]( std::size_t index ) const {
        try {
            if (ElementNumber == 0) {
                throw EmptySnakeBodyDataStruct();
            }
            if (index > ElementNumber or index < 0) {
                throw std::out_of_range( "Snake body index out of range" );
            }
            return Body[index];
        } catch (const EmptySnakeBodyDataStruct& e) {
            std::cerr << "Error: " << e.what();
            std::cout << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what();
            std::cout << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    Vector& operator=( const std::initializer_list<type> list ) {
        ElementNumber = list.size();
        int i = 0;
        for (const auto& it : list) {
            this->Body[i++] = it;
        }
        return *this;
    }
    Vector& operator=(const Vector& other)
    {
        if (this == &other)
            return *this;

        delete[] Body;

        capacity = other.capacity;
        ElementNumber = other.ElementNumber;

        if (capacity == 0)
        {
            Body = nullptr;
        }
        else
        {
            Body = new type[capacity];

            for (std::size_t i = 0; i < ElementNumber; i++)
            {
                Body[i] = other.Body[i];
            }
        }

        return *this;
    }
    ~Vector() {
        delete[] Body;
    }
};
