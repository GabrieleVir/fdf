int		trans_map(t_map **maps, int width, int height)
{
	int		i;
	int		lines;
	int		columns;
	int		x;
	int		y;
	int		z;
	int		dz;

	dz = (*maps)->highest_point - (*maps)->lowest_point;
	lines = (*maps)->lines;
	columns = (*maps)->columns;
	i = -1;
	if (((*maps)->distance_x = width / (columns * 4)) < 10)
		(*maps)->distance_x = 5;
	if (((*maps)->distance_y = height / (lines * 4)) < 10)
		(*maps)->distance_y = 5;
	if (((*maps)->highest_point + (*maps)->lowest_point) > (*maps)->distance_y)
		(*maps)->distance_z = 5;
	else
		(*maps)->distance_z = 10;
	if (!((*maps)->trans_map = (int*)malloc(sizeof(int) * lines * columns * 3)))
		return (error_management("trans_map", "malloc"));
	while (++i < lines * columns)
	{
		x = i % columns * (*maps)->distance_x;
		y = i / columns * (*maps)->distance_y;
		z = (*maps)->default_map[i] * (*maps)->distance_z;
		(*maps)->trans_map[i * 3] = x * cos(0.523599) - y * cos(0.523599);
		(*maps)->trans_map[i * 3 + 1] = x * sin(0.523599) + y * sin(0.523599) - z;
		(*maps)->trans_map[i * 3 + 2] = z;
	}
	return (1);
}
