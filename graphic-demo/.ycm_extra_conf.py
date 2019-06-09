import os

def Settings( **kwargs ):
    return {'flags': [ '-x', 'c++', '-Wall', f'-I{os.environ["VITASDK"]}/arm-vita-eabi/include', '-I../common'],}
