namespace ModMaid.DoxyParser.Models.Yaml;

public class YamlNamespace
{
  public required string Id { get; set; }
  public required string Name { get; set; }

  public required List<YamlClassReference> Classes { get; set; }
  public required List<YamlAlias> Aliases { get; set; }
  public required List<YamlGlobal> Globals { get; set; }
  public required List<YamlFunction> Functions { get; set; }
}

public class YamlClassReference
{
  public required string Id { get; set; }
  public required string Name { get; set; }
}

public class YamlAlias
{
  public required string Id { get; set; }
  public required string Name { get; set; }
  public required string BaseType { get; set; }
}

public class YamlGlobal
{
  public required string Id { get; set; }
  public required string Name { get; set; }
  public required string Type { get; set; }
}

public class YamlFunction
{
  public required string Id { get; set; }
  public required string Name { get; set; }
  public required string ReturnType { get; set; }
}
