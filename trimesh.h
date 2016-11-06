#ifndef TRIMESH_H
#define TRIMESH_H


class Trimesh : public PhysicalSingleBody{
private:
    static string geometry;

protected:
    void OnSetSettings();
    bool HandleMessage(NodeMessage message);

public:
    void Draw();


};

#endif // TRIMESH_H
