import json
from pycparser import parse_file, c_ast

def ast_to_dict(node):
    if isinstance(node, c_ast.Node):
        result = {'type': node.__class__.__name__}
        for name, child in node.children():
            result[name] = ast_to_dict(child)
        return result
    elif isinstance(node, list):
        return [ast_to_dict(item) for item in node]
    else:
        return node

ast = parse_file('trainers.h', use_cpp=True)
print(ast_to_dict(ast))
#data = ast_to_dict(ast)

#with open('output.json', 'w') as f:
#    json.dump(data, f, indent=2)