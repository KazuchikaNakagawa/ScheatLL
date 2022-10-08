#if !defined(SCHEATLLERROR_HPP)
#define SCHEATLLERROR_HPP

#include <stdexcept>

namespace scheat
{

class scheat_error : public std::exception
{
public:
    scheat_error() {};

    // return the reason, not the solution.
    virtual const char* what() const noexcept override = 0;
    ~scheat_error() {};
};

// happens when an unsuitable value, such as nullptr, was given for the functions.
class scheat_value_error : public scheat_error
{
public:
    scheat_value_error() {};
    virtual const char* what() const noexcept override {
        return "unsuitable value was given";
    }
    ~scheat_value_error() {};
};

class scheat_expected_value_error : public scheat_error
{
public:
    scheat_expected_value_error() {};
    virtual const char* what() const noexcept override {
        return "clause does not have any values.";
    }
    ~scheat_expected_value_error() {};
};

class scheat_readability_error : public scheat_error
{
public:
    scheat_readability_error() {};
    virtual const char* what() const noexcept override {
        return "tried to read unreadable value";
    }
    ~scheat_readability_error() {};
};

class scheat_writability_error : public scheat_error
{
public:
    scheat_writability_error() {};
    virtual const char* what() const noexcept override {
        return "tried to write to unwritable value";
    }
    ~scheat_writability_error() {};
};

// happens when impossible attribute --writable functions is created.
class scheat_attribute_error : public scheat_error
{
public:
    scheat_attribute_error() {};
    virtual const char* what() const noexcept override {
        return "impossible attribute is generated";
    }
    ~scheat_attribute_error() {};
};

class scheat_name_not_exist_error : public scheat_error
{
public:
    scheat_name_not_exist_error() {};
    virtual const char* what() const noexcept override {
        return "given name does not exist";
    }
    ~scheat_name_not_exist_error() {};
};

class scheat_operator_not_exist_error : public scheat_error
{
public:
    scheat_operator_not_exist_error() {};
    virtual const char* what() const noexcept override {
        return "given operator does not exist";
    }
    ~scheat_operator_not_exist_error() {};
};

class scheat_name_already_defined_error : public scheat_error
{
public:
    scheat_name_already_defined_error() {};
    virtual const char* what() const noexcept override {
        return "name already defined so cannot be used";
    }
    ~scheat_name_already_defined_error() {};
};

class scheat_type_error : public scheat_error
{
public:
    scheat_type_error() {};
    virtual const char* what() const noexcept override {
        return "types are not compatible";
    }
    ~scheat_type_error() {};
};

class scheat_callee_error : public scheat_error
{
public:
    scheat_callee_error() {};
    virtual const char* what() const noexcept override {
        return "cannot call non-function value";
    }
    ~scheat_callee_error() {};
};

class scheat_return_error : public scheat_error
{
public:
    scheat_return_error() {};
    virtual const char* what() const noexcept override {
        return "function return type error";
    }
    ~scheat_return_error() {};
};

class scheat_unavailable_feature_error : public scheat_error
{
public:
    scheat_unavailable_feature_error() {};
    virtual const char* what() const noexcept override {
        return "this feature is not available yet";
    }
    ~scheat_unavailable_feature_error() {};
};

} // namespace scheat


#endif // SCHEATLLERROR_HPP
