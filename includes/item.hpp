#ifndef SOLUTION_HPP
#define SOLUTION_HPP
class Item {
    public:
        virtual void Draw() = 0;
        virtual void Interact() = 0;
        void Drop();
        void Pick();
    private:
        int inventory_idx;
};
#endif