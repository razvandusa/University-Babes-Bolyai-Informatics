def sum_of_hours(program : list) -> int:
    """
    Programul face suma tuturor emisiunilor din lista
    :param program: lista cu emisiuni
    :return: suma
    """
    suma = 0
    for emisiune in program:
        suma += emisiune.durata
    return suma