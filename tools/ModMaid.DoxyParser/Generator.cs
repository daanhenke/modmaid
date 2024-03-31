using System.Xml.Serialization;
using ModMaid.DoxyParser.Models.Xml;
using YamlDotNet.Serialization;
using YamlDotNet.Serialization.NamingConventions;

namespace ModMaid.DoxyParser;

public class Generator
{
  private readonly GeneratorConfiguration _configuration;
  private readonly TypeMapper _mapper = new ();

  public Generator(GeneratorConfiguration configuration)
  {
    _configuration = configuration;
  }

  public void Generate()
  {
    var index = ParseIndex();

    foreach (var compound in index.Children.Where(c => c.Kind == DoxyMemberKind.Namespace))
    {
      GenerateNamespace(compound);
    }

    foreach (var compound in index.Children.Where(c => c.Kind == DoxyMemberKind.Class))
    {
      GenerateClass(compound);
    }
  }

  private void GenerateClass(DoxyCompound compound)
  {
    var root = FromXml<DoxyRoot>(Path.Combine(_configuration.InPath, $"{compound.ReferenceId}.xml"));
    var normalizedId = NormalizeId(root.CompoundDefinition.Id, "class", "modmaid");
    ToYaml(root, Path.Combine(_configuration.OutPath, "classes", $"{normalizedId}.yml"));
  }

  private void GenerateNamespace(DoxyCompound compound)
  {
    var root = FromXml<DoxyRoot>(Path.Combine(_configuration.InPath, $"{compound.ReferenceId}.xml"));
    var normalizedId = NormalizeId(root.CompoundDefinition.Id, "namespace", "modmaid");

    ToYaml(_mapper.ConvertNamespace(root.CompoundDefinition), Path.Combine(_configuration.OutPath, "namespaces", $"{normalizedId}.yml"));
  }

  private DoxyIndex ParseIndex()
  {
    var index = FromXml<DoxyIndex>(Path.Combine(_configuration.InPath, "index.xml"));

    return index;
  }

  private static string NormalizeId(string id, string type, string prefix)
  {
    string result;

    var normalized = id
      .Replace("_1_1_", ".")
      .Replace("_1_1", ".");
    var fullPrefix = $"{type}{prefix}.";

    if (normalized.Length <= fullPrefix.Length)
    {
      result = "index";
    }
    else
    {
      result = normalized.Substring(fullPrefix.Length);
    }

    Console.WriteLine($"{id} -> {result}.yml");
    return result;
  }

  private static T FromXml<T>(string filePath)
    where T : class
  {
    if (!File.Exists(filePath))
    {
      throw new FileNotFoundException(filePath);
    }

    using var fileStream = new FileStream(filePath, FileMode.Open);

    var serializer = new XmlSerializer(typeof(T));
    var result = serializer.Deserialize(fileStream) as T;

    if (result is null)
    {
      throw new NotSupportedException();
    }

    return result;
  }


  private static void ToYaml<T>(T value, string filePath)
    where T : class
  {
    var parentPath = Directory.GetParent(filePath)?.FullName;
    if (parentPath is null)
    {
      throw new NotImplementedException();
    }
    else if (!Directory.Exists(parentPath))
    {
      Directory.CreateDirectory(parentPath);
    }

    var serializer = new SerializerBuilder()
      .WithNamingConvention(CamelCaseNamingConvention.Instance)
      .Build();

    File.WriteAllText(filePath, serializer.Serialize(value));
  }
}
