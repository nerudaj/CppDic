#pragma once

#include <memory>
#include <print>

struct A
{
};

struct B
{
};

struct C
{
};

struct D
{
    D(A, B, C) {}
};

struct E
{
    E(A, B) {}
};

struct Eshared
{
    Eshared(std::shared_ptr<A>, std::shared_ptr<B>) {}

    void hello()
    {
        std::println("Hello");
    }
};

struct I
{
    virtual ~I() = default;
    virtual int foo() = 0;
};

struct Ia : public I
{
    int foo() override
    {
        return 42;
    };
};

struct Ib : public I
{
    int foo() override
    {
        return 69;
    };
};

struct IEshared : public I
{
    IEshared(std::shared_ptr<A>) {}

    int foo() override
    {
        return 88;
    };
};