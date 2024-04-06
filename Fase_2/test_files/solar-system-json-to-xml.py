import json
import xml.dom.minidom as minidom
from enum import IntEnum
import random

SPHERE_MODEL = 'sphere_1_12_12.3d'
RING_MODEL = 'ring_3_4_20.3d'


class Transform:
    class Type(IntEnum):
        TRANSLATE = 0
        ROTATE = 1
        SCALE = 2
    
    def __init__(self, type: Type, x, y, z, angle=0):
        self.type = type
        self.x = x
        self.y = y
        self.z = z
        self.angle = angle


def create_window(doc, world):
    window = doc.createElement("window")
    window.setAttribute("width", "512")
    window.setAttribute("height", "512")
    world.appendChild(window)


def create_camera(doc, world):
    camera = doc.createElement("camera")

    position = doc.createElement("position")
    position.setAttribute("x", "200")
    position.setAttribute("y", "200")
    position.setAttribute("z", "200")
    camera.appendChild(position)
    
    lookAt = doc.createElement("lookAt")
    lookAt.setAttribute("x", "0")
    lookAt.setAttribute("y", "0")
    lookAt.setAttribute("z", "0")
    camera.appendChild(lookAt)
    
    up = doc.createElement("up")
    up.setAttribute("x", "0")
    up.setAttribute("y", "1")
    up.setAttribute("z", "0")
    camera.appendChild(up)
    
    projection = doc.createElement("projection")
    projection.setAttribute("fov", "90")
    projection.setAttribute("near", "200")
    projection.setAttribute("far", "7200")
    camera.appendChild(projection)
    
    world.appendChild(camera)


def create_scale(doc, obj):
    scale = doc.createElement('scale')
    r = str(round((obj['diameter'] / 2.0) / 1000.0)) # tecnicamente devia ser a dividir por 1000000 para ficar à
                                                     # escala porque a distância entre os planetas e o sol está em 10^6
    scale.setAttribute('x', r)
    scale.setAttribute('y', r)
    scale.setAttribute('z', r)
    return scale


def create_scale_xyz(doc, x, y, z):
    scale = doc.createElement('scale')
    scale.setAttribute('x', x)
    scale.setAttribute('y', y)
    scale.setAttribute('z', z)
    return scale


def create_translate(doc, obj):
    translate = doc.createElement('translate')
    distance_from_sun = str(round(obj['distanceFromSun']))
    translate.setAttribute('x', distance_from_sun)
    translate.setAttribute('y', '0')
    translate.setAttribute('z', '0')
    return translate

def create_rotate(doc, max_x, y, max_z, max_angle):
    rotate = doc.createElement('rotate')
    rotate_x = str(round(random.uniform(0, max_x)))
    rotate_y = str(y)
    rotate_z = str(round(random.uniform(0, max_z)))
    angle = str(round(random.uniform(0, max_angle)))
    rotate.setAttribute('x', rotate_x)
    rotate.setAttribute('y', rotate_y)
    rotate.setAttribute('z', rotate_z)
    rotate.setAttribute('angle', angle)
    return rotate


def create_groups(doc, world, data):
    for obj in data:
        group = doc.createElement('group')
        
        if obj['hasRingSystem']:
            transform = doc.createElement('transform')
            
            rotate = create_rotate(doc, 0.2, 1, 0.2, 360)
            transform.appendChild(rotate)
            
            translate = create_translate(doc, obj)
            transform.appendChild(translate)
            
            scale = create_scale(doc, obj)
            transform.appendChild(scale)
            
            group.appendChild(transform)
            
            models = create_models(doc, SPHERE_MODEL)
            group.appendChild(models)    

            group_ring = doc.createElement('group')
            transform = doc.createElement('transform')
            rotate = create_rotate(doc, 0.2, 0, 0.2, 360)
            transform.appendChild(rotate)
            group_ring.appendChild(transform)
            
            models = create_models(doc, RING_MODEL)
            group_ring.appendChild(models)  
            
            group.appendChild(group_ring)
            
        else:
            group = doc.createElement('group')
            transform = doc.createElement('transform')
            
            rotate = create_rotate(doc, 0.2, 1, 0.2, 360)
            transform.appendChild(rotate)
            
            translate = create_translate(doc, obj)
            transform.appendChild(translate)
            
            scale = create_scale(doc, obj)
            transform.appendChild(scale)
            
            group.appendChild(transform)
            
            models = create_models(doc, SPHERE_MODEL)
            group.appendChild(models)    
            
        world.appendChild(group)
    
    
def create_models(doc, model_file):
    models = doc.createElement('models')
    model = doc.createElement('model')
    model.setAttribute('file', model_file)
    models.appendChild(model)
    return models


def main():
    # o sol não está completamente à escala, o diametro devia ser 1391400 e não 1391400
    with open('planets_and_sun.json', 'r') as file:
        data = json.load(file)
                
    doc = minidom.Document()
    world = doc.createElement("world")
    doc.appendChild(world)
    
    create_window(doc, world)
    create_camera(doc, world)
    create_groups(doc, world, data)
    
    with open("test_2_6.xml", "w", encoding="utf-8") as xml_file:
        xml_file.write(doc.toprettyxml(indent="\t").split('\n', 1)[1])


if __name__ == '__main__':
    main()
