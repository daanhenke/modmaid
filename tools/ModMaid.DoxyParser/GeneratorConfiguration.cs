namespace ModMaid.DoxyParser;

public class GeneratorConfiguration
{
  public required string InPath { get; set; }
  public required string OutPath { get; set; }

  public static GeneratorConfiguration GetDefault()
  {
    var currDir = AppDomain.CurrentDomain.BaseDirectory;
    var projectDir = Directory.GetParent(currDir)?
      .Parent?
      .Parent?
      .Parent?
      .Parent?
      .FullName;

    if (projectDir is null) throw new ArgumentException();

    return new()
    {
      InPath = Path.Combine(projectDir, "build", "cmake", "docs", "xml"),
      OutPath = Path.Combine(projectDir, "website", "content", "docs")
    };
  }
}
