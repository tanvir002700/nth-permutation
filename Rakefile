require "rake/extensiontask"

Rake::ExtensionTask.new "nth_permutation" do |ext|
  ext.lib_dir = "lib/nth_permutation"
end

require "bundler/gem_tasks"
require "rspec/core/rake_task"

RSpec::Core::RakeTask.new(:spec)

task :default => :spec
