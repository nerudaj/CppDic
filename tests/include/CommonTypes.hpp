#pragma once

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