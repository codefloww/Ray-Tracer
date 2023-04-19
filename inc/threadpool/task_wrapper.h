#ifndef INTEGRATE_PARALLEL_QUEUE_TASK_WRAPPER_H
#define INTEGRATE_PARALLEL_QUEUE_TASK_WRAPPER_H
#include <memory>

class task_wrapper {
public:
    struct wrapped_task_base{
        virtual void call() = 0;
        virtual ~wrapped_task_base()= default;
    };

    std::unique_ptr<wrapped_task_base> implemented_function_ptr;

    template<typename functionType, typename argumentsContainerType, typename promiseType>
    struct wrapped_task_with_args: wrapped_task_base{
    private:
        functionType &function;
        argumentsContainerType arguments;
        promiseType promise;
    public:
        wrapped_task_with_args(functionType &givenFunction, argumentsContainerType &argumentsContainer,
                               promiseType &promise):
                function(givenFunction), arguments(argumentsContainer), promise(std::move(promise)){}
        void call() override{
            auto a = function(arguments);
            promise.set_value(a);
        }
    };

    template<typename functionType, typename promiseType>
    struct wrapped_task_no_args: wrapped_task_base{
    private:
        functionType &function;
        promiseType promise;
    public:
        wrapped_task_no_args(functionType &givenFunction, promiseType &promise):
                function(givenFunction), promise(std::move(promise)){}
        void call() override{
            auto a = function();
            promise.set_value(a);
        }
    };

    template<typename functionType, typename argumentsContainerType, typename promiseType>
    task_wrapper(functionType& function, argumentsContainerType& arguments, promiseType& promise):
        implemented_function_ptr(new wrapped_task_with_args<functionType,
                                 argumentsContainerType, promiseType>(function, arguments, promise))
    {}

    template<typename functionType, typename promiseType>
    task_wrapper(functionType& function, promiseType& promise):
            implemented_function_ptr(new wrapped_task_no_args<functionType, promiseType>(function, promise))
    {}

    void operator()(){
        implemented_function_ptr->call();
    }

    task_wrapper(task_wrapper&& other) noexcept :
    implemented_function_ptr(std::move(other.implemented_function_ptr))
    {}

    task_wrapper& operator=(task_wrapper&& other) noexcept {
        implemented_function_ptr = std::move(other.implemented_function_ptr);
        return *this;
    }

    task_wrapper() = default;
    task_wrapper(task_wrapper&)=delete;
    task_wrapper& operator=(const task_wrapper&)=delete;
};


#endif //INTEGRATE_PARALLEL_QUEUE_TASK_WRAPPER_H
