class Tiles{
    public:
        Tiles(){};
        virtual void changeState(char x)=0;
        virtual int getSize(void)=0;
        virtual char getChar(int x, int y)=0;
        virtual void updateY()=0;
        virtual void updateX(char key)=0;
        virtual int getPosX()=0;
        virtual int getPosY()=0;
        virtual int getEndX()=0;
        virtual int getEndY()=0;
        virtual ~Tiles(){};
    private:
        int x;
};